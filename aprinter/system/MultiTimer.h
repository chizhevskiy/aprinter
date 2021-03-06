/*
 * Copyright (c) 2017 Ambroz Bizjak
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef APRINTER_MULTI_TIMER_H
#define APRINTER_MULTI_TIMER_H

#include <aprinter/meta/ChooseInt.h>
#include <aprinter/meta/TypeListUtils.h>
#include <aprinter/meta/ListForEach.h>
#include <aprinter/base/Preprocessor.h>
#include <aprinter/base/Assert.h>
#include <aprinter/misc/ClockUtils.h>

#include <aprinter/BeginNamespace.h>

template <typename TimedEvent, typename MT, typename TimerId>
class MultiTimerOne
{
    APRINTER_USE_TYPES1(TimedEvent, (Context, TimeType))
    
public:
    inline bool isSet (Context c)
    {
        return (mt().m_state & MT::TimerBit(TimerId())) != 0;
    }
    
    inline TimeType getSetTime (Context c)
    {
        return mt().m_times[MT::TimerIndex(TimerId())];
    }
    
    inline void appendAtNotAlready (Context c, TimeType time)
    {
        AMBRO_ASSERT(!isSet(c))
        appendAt(c, time);
    }
    
    void appendAt (Context c, TimeType time)
    {
        mt().m_times[MT::TimerIndex(TimerId())] = time;
        mt().m_state |= MT::TimerBit(TimerId());
        mt().updateTimer(c);
    }
    
    void appendNowNotAlready (Context c)
    {
        appendAtNotAlready(c, Context::Clock::getTime(c));
    }
    
    void appendAfter (Context c, TimeType after_time)
    {
        appendAt(c, Context::Clock::getTime(c) + after_time);
    }
    
    void appendAfterNotAlready (Context c, TimeType after_time)
    {
        appendAtNotAlready(c, Context::Clock::getTime(c) + after_time);
    }
    
    void appendAfterPrevious (Context c, TimeType after_time)
    {
        appendAtNotAlready(c, getSetTime(c) + after_time);
    }
    
    void unset (Context c)
    {
        mt().m_state &= ~MT::TimerBit(TimerId());
        mt().updateTimer(c);
    }
    
private:
    inline MT & mt ()
    {
        return static_cast<MT &>(*this);
    }
};

template <typename TimedEvent, typename Impl, typename UserData, typename... TimerIds>
class MultiTimer :
    private MultiTimerOne<TimedEvent, MultiTimer<TimedEvent, Impl, UserData, TimerIds...>, TimerIds>...,
    private TimedEvent,
    public UserData
{
    template <typename, typename, typename>
    friend class MultiTimerOne;
    
    APRINTER_USE_TYPES1(TimedEvent, (Context, TimeType))
    using TheClockUtils = ClockUtils<Context>;
    
    static int const NumTimers = sizeof...(TimerIds);
    using TimerIdsList = MakeTypeList<TimerIds...>;
    
    using StateType = ChooseInt<NumTimers, false>;
    
    template <typename TimerId>
    static constexpr int TimerIndex (TimerId)
    {
        return TypeListIndex<TimerIdsList, TimerId>::Value;
    }
    
    template <typename TimerId>
    static constexpr StateType TimerBit (TimerId)
    {
        return (StateType)1 << TimerIndex(TimerId());
    }
    
private:
    // UserData would be placed in front of m_state using up
    // what might otherwise be holes in the memory layout.
    StateType m_state;
    TimeType m_times[NumTimers];
    
public:
    inline void init (Context c)
    {
        TimedEvent::init(c);
        m_state = 0;
    }
    
    inline void deinit (Context c)
    {
        TimedEvent::deinit(c);
    }
    
    inline void unsetAll (Context c)
    {
        TimedEvent::unset(c);
        m_state = 0;
    }
    
    template <typename TimerId>
    inline MultiTimerOne<TimedEvent, MultiTimer, TimerId> & tim (TimerId)
    {
        return static_cast<MultiTimerOne<TimedEvent, MultiTimer, TimerId> &>(*this);
    }
    
private:
    void updateTimer (Context c)
    {
        StateType state = m_state;
        
        if (state == 0) {
            // No user timer is set, unset the underlying timer.
            TimedEvent::unset(c);
            return;
        }
        
        // This is the value with the most significant bit one and others zero.
        constexpr TimeType msb = ((TimeType)-1 / 2) + 1;
        
        // We use this as the base time to compare timers to. We will also
        // be computing the minium time relative to this time for efficiency.
        TimeType ref_time = Context::EventLoop::getEventTime(c) - msb;
        
        // State for the minimum calculation.
        TimeType min_time_rel = (TimeType)-1;
        
        // Go through all timers to find the minimum time.
        ListFor<TimerIdsList>([&] APRINTER_TL(TimerId, {
            if ((state & MultiTimer::TimerBit(TimerId())) != 0) {
                TimeType time_rel = m_times[MultiTimer::TimerIndex(TimerId())] - ref_time;
                if (time_rel < min_time_rel) {
                    min_time_rel = time_rel;
                }
            }
        }));
        
        // Set the underlying timer to the minimum time.
        TimeType min_time = min_time_rel + ref_time;
        TimedEvent::appendAt(c, min_time);
    }
    
    void handleTimerExpired (Context c) override final
    {
        TimeType set_time = TimedEvent::getSetTime(c);
        
        bool not_handled = ListForBreak<TimerIdsList>([&] APRINTER_TL(TimerId,
        {
            if ((m_state & MultiTimer::TimerBit(TimerId())) != 0 &&
                m_times[MultiTimer::TimerIndex(TimerId())] == set_time)
            {
                m_state &= ~MultiTimer::TimerBit(TimerId());
                this->updateTimer(c);
                static_cast<Impl *>(this)->timerExpired(TimerId(), c);
                return false;
            }
            return true;
        }));
        
        AMBRO_ASSERT(!not_handled)
    }
};

#include <aprinter/EndNamespace.h>

#endif
