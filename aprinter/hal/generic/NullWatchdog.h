/*
 * Copyright (c) 2015 Ambroz Bizjak
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

#ifndef AMBROLIB_NULL_WATCHDOG_H
#define AMBROLIB_NULL_WATCHDOG_H

#include <stdlib.h>

#include <aprinter/meta/ServiceUtils.h>
#include <aprinter/base/Preprocessor.h>
#include <aprinter/base/Object.h>
#include <aprinter/base/DebugObject.h>
#include <aprinter/base/Hints.h>

#include <aprinter/BeginNamespace.h>

template <typename Arg>
class NullWatchdog {
    APRINTER_USE_TYPES1(Arg, (Context, ParentObject))
    
public:
    struct Object;
    
private:
    using TheDebugObject = DebugObject<Context, Object>;
    
public:
    static constexpr double WatchdogTime = 1000.0;
    
    static void init (Context c)
    {
        TheDebugObject::init(c);
    }
    
    static void deinit (Context c)
    {
        TheDebugObject::deinit(c);
    }
    
    template <typename ThisContext>
    static void reset (ThisContext c)
    {
        TheDebugObject::access(c);
    }
    
    APRINTER_NO_RETURN
    static void emergency_abort ()
    {
        ::abort();
    }
    
public:
    struct Object : public ObjBase<NullWatchdog, ParentObject, MakeTypeList<TheDebugObject>> {};
};

struct NullWatchdogService {
    APRINTER_ALIAS_STRUCT_EXT(Watchdog, (
        APRINTER_AS_TYPE(Context),
        APRINTER_AS_TYPE(ParentObject),
        APRINTER_AS_VALUE(bool, DebugMode)
    ), (
        APRINTER_DEF_INSTANCE(Watchdog, NullWatchdog)
    ))
};

#include <aprinter/EndNamespace.h>

#endif
