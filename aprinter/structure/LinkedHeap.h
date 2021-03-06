/*
 * Copyright (c) 2016 Ambroz Bizjak
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

#ifndef APRINTER_LINKED_HEAP_H
#define APRINTER_LINKED_HEAP_H

#include <stddef.h>

#include <type_traits>
#include <limits>

#include <aprinter/base/Assert.h>

#include <aprinter/BeginNamespace.h>

//#define APRINTER_LINKED_HEAP_VERIFY 1

template<typename, typename, typename, typename>
class LinkedHeap;

template <typename LinkModel>
class LinkedHeapNode {
    template<typename, typename, typename, typename>
    friend class LinkedHeap;
    
    using Link = typename LinkModel::Link;
    
private:
    Link parent;
    Link link[2];
};

template <
    typename Accessor,
    typename Compare,
    typename LinkModel,
    typename SizeType = size_t
>
class LinkedHeap
{
    static_assert(std::is_unsigned<SizeType>::value, "");
    
    using Link = typename LinkModel::Link;
    
private:
    Link m_root;
    Link m_last;
    SizeType m_count;
    SizeType m_level_bit;
    
public:
    using State = typename LinkModel::State;
    using Ref = typename LinkModel::Ref;
    
    inline void init ()
    {
        m_root = Link::null();
        m_count = 0;
    }
    
    inline Ref first (State st = State()) const
    {
        return m_root.ref(st);
    }
    
    void insert (Ref node, State st = State())
    {
        AMBRO_ASSERT(m_count < std::numeric_limits<SizeType>::max())
        AMBRO_ASSERT(m_root.isNull() == (m_count == 0))
        
        if (m_root.isNull()) {
            m_root = node.link();
            m_last = node.link();
            m_count = 1;
            m_level_bit = 1;
            
            ac(node).parent = Link::null();
            ac(node).link[0] = Link::null();
            ac(node).link[1] = Link::null();
            
            assertValidHeap(st);
            return;
        }
        
        SizeType prev_count = increment_count();
        SizeType new_count = m_count;
        bool from_root = should_walk_from_root(prev_count, new_count);
        
        Ref cur;
        bool dir;
        
        if (from_root) {
            SizeType bit = m_level_bit;
            cur = m_root.ref(st);
            
            while (bit > 2) {
                bit >>= 1;
                bool next_dir = (new_count & bit) != 0;
                
                AMBRO_ASSERT(!ac(cur).link[next_dir].isNull())
                cur = ac(cur).link[next_dir].ref(st);
            }
            
            bit >>= 1;
            dir = (new_count & bit) != 0;
        } else {
            cur = m_last.ref(st);
            Ref parent = ac(cur).parent.ref(st);
            AMBRO_ASSERT(!parent.isNull())
            
            while (cur.link() == ac(parent).link[1]) {
                AMBRO_ASSERT(!ac(cur).parent.isNull())
                cur = parent;
                parent = ac(cur).parent.ref(st);
            }
            
            if (!ac(parent).link[1].isNull()) {
                cur = ac(parent).link[1].ref(st);
                dir = false;
                
                while (!ac(cur).link[0].isNull()) {
                    cur = ac(cur).link[0].ref(st);
                }
            } else {
                cur = parent;
                dir = true;
            }
        }
        
        Ref parent = cur;
        AMBRO_ASSERT(ac(parent).link[dir].isNull())
        AMBRO_ASSERT(ac(parent).link[1].isNull())
        
        if (Compare::compareEntries(st, parent, node) <= 0) {
            m_last = node.link();
            
            ac(parent).link[dir] = node.link();
            
            ac(node).parent = parent.link();
            ac(node).link[0] = Link::null();
            ac(node).link[1] = Link::null();
        } else {
            m_last = parent.link();
            
            Link sibling = ac(parent).link[!dir];
            
            ac(parent).link[0] = Link::null();
            ac(parent).link[1] = Link::null();
            
            bubble_up_node(st, node, parent, sibling, dir);
        }
        
        assertValidHeap(st);
    }
    
    void remove (Ref node, State st = State())
    {
        AMBRO_ASSERT(!m_root.isNull() && m_count > 0)
        
        if (m_count == 1) {
            m_root = Link::null();
            m_count = 0;
            
            assertValidHeap(st);
            return;
        }
        
        SizeType prev_count = decrement_count();
        SizeType new_count = m_count;
        bool from_root = should_walk_from_root(prev_count, new_count);
        
        Ref cur;
        
        if (from_root) {
            Ref last_parent = ac(m_last.ref(st)).parent.ref(st);
            ac(last_parent).link[m_last == ac(last_parent).link[1]] = Link::null();
            
            SizeType bit = m_level_bit;
            cur = m_root.ref(st);
            
            while (bit > 1) {
                bit >>= 1;
                bool next_dir = (new_count & bit) != 0;
                
                AMBRO_ASSERT(!ac(cur).link[next_dir].isNull())
                cur = ac(cur).link[next_dir].ref(st);
            }
        } else {
            cur = m_last.ref(st);
            Ref parent = ac(cur).parent.ref(st);
            AMBRO_ASSERT(!parent.isNull())
            
            bool dir = cur.link() == ac(parent).link[1];
            ac(parent).link[dir] = Link::null();
            
            if (dir) {
                AMBRO_ASSERT(!ac(parent).link[0].isNull())
                cur = ac(parent).link[0].ref(st);
                
                AMBRO_ASSERT(ac(cur).link[0].isNull())
                AMBRO_ASSERT(ac(cur).link[1].isNull())
            } else {
                do {
                    cur = parent;
                    AMBRO_ASSERT(!ac(cur).parent.isNull())
                    parent = ac(cur).parent.ref(st);
                } while (cur.link() == ac(parent).link[0]);
                
                AMBRO_ASSERT(!ac(parent).link[0].isNull())
                cur = ac(parent).link[0].ref(st);
                
                AMBRO_ASSERT(!ac(cur).link[1].isNull())
                do {
                    cur = ac(cur).link[1].ref(st);
                } while (!ac(cur).link[1].isNull());
            }
        }
        
        Ref srcnode = m_last.ref(st);
        
        if (!(node == cur)) {
            m_last = cur.link();
        }
        
        if (!(node == srcnode)) {
            Ref parent = ac(node).parent.ref(st);
            bool side = !parent.isNull() && node.link() == ac(parent).link[1];
            Link child0 = ac(node).link[0];
            Link child1 = ac(node).link[1];
            
            if (!parent.isNull() && Compare::compareEntries(st, srcnode, parent) < 0) {
                Link sibling = ac(parent).link[!side];
                
                if (!(ac(parent).link[0] = child0).isNull()) {
                    ac(child0.ref(st)).parent = parent.link();
                }
                
                if (!(ac(parent).link[1] = child1).isNull()) {
                    ac(child1.ref(st)).parent = parent.link();
                }
                
                if (m_last == srcnode.link()) {
                    m_last = parent.link();
                }
                
                bubble_up_node(st, srcnode, parent, sibling, side);
            } else {
                connect_and_bubble_down_node(st, srcnode, parent, side, child0, child1);
            }
        }
        
        assertValidHeap(st);
    }
    
    void fixup (Ref node, State st = State())
    {
        AMBRO_ASSERT(!m_root.isNull() && m_count > 0)
        
        if (m_count == 1) {
            assertValidHeap(st);
            return;
        }
        
        Ref parent = ac(node).parent.ref(st);
        if (!parent.isNull() && Compare::compareEntries(st, node, parent) < 0) {
            Link child0 = ac(node).link[0];
            Link child1 = ac(node).link[1];
            
            bool side = node.link() == ac(parent).link[1];
            Link sibling = ac(parent).link[!side];
            
            if (!(ac(parent).link[0] = child0).isNull()) {
                ac(child0.ref(st)).parent = parent.link();
            }
            
            if (!(ac(parent).link[1] = child1).isNull()) {
                ac(child1.ref(st)).parent = parent.link();
            }
            
            if (m_last == node.link()) {
                m_last = parent.link();
            }
            
            bubble_up_node(st, node, parent, sibling, side);
        } else {
            bubble_down_node_if_needed(st, node);
        }
        
        assertValidHeap(st);
    }
    
    template <typename KeyType>
    Ref findFirstLesserOrEqual (KeyType key, State st = State())
    {
        Ref root = m_root.ref(st);
        if (!root.isNull() && Compare::compareKeyEntry(st, key, root) >= 0) {
            return root;
        }
        
        return Ref::null();
    }
    
    template <typename KeyType>
    Ref findNextLesserOrEqual (KeyType key, Ref node, State st = State())
    {
        AMBRO_ASSERT(!node.isNull())
        AMBRO_ASSERT(Compare::compareKeyEntry(st, key, node) >= 0)
        
        for (bool side : {false, true}) {
            Ref child = ac(node).link[side].ref(st);
            if (!child.isNull() && Compare::compareKeyEntry(st, key, child) >= 0) {
                return child;
            }
        }
        
        Ref parent = ac(node).parent.ref(st);
        
        while (!parent.isNull()) {
            AMBRO_ASSERT(Compare::compareKeyEntry(st, key, parent) >= 0)
            
            if (!(node.link() == ac(parent).link[1])) {
                AMBRO_ASSERT(node.link() == ac(parent).link[0])
                
                Ref sibling = ac(parent).link[1].ref(st);
                if (!sibling.isNull() && Compare::compareKeyEntry(st, key, sibling) >= 0) {
                    return sibling;
                }
            }
            
            node = parent;
            parent = ac(node).parent.ref(st);
        }
        
        return Ref::null();
    }
    
    inline void assertValidHeap (State st = State())
    {
#if APRINTER_LINKED_HEAP_VERIFY
        verifyHeap(st);
#endif
    }
    
    void verifyHeap (State st = State())
    {
        if (m_root.isNull()) {
            AMBRO_ASSERT_FORCE(m_count == 0)
            return;
        }
        
        AssertData ad;
        ad.state = AssertState::NoDepth;
        ad.prev_leaf = Link::null();
        ad.count = 0;
        
        AMBRO_ASSERT_FORCE(!m_last.isNull())
        AMBRO_ASSERT_FORCE(ac(m_root.ref(st)).parent.isNull())
        
        assert_recurser(st, m_root.ref(st), ad, 0);
        
        AMBRO_ASSERT_FORCE(ad.prev_leaf == m_last)
        AMBRO_ASSERT_FORCE(ad.count == m_count)
        
        int bits = 0;
        SizeType x = m_count;
        while (x > 0) {
            x /= 2;
            bits++;
        }
        AMBRO_ASSERT_FORCE(m_level_bit == ((SizeType)1 << (bits - 1)))
    }
    
private:
    inline static LinkedHeapNode<LinkModel> & ac (Ref ref)
    {
        return Accessor::access(*ref);
    }
    
    inline SizeType increment_count ()
    {
        SizeType prev_count = m_count;
        m_count = prev_count + 1;
        SizeType next_level_bit = 2 * m_level_bit;
        if (m_count == next_level_bit) {
            m_level_bit = next_level_bit;
        }
        return prev_count;
    }
    
    inline SizeType decrement_count ()
    {
        SizeType prev_count = m_count;
        m_count = prev_count - 1;
        if (prev_count == m_level_bit) {
            m_level_bit = m_level_bit / 2;
        }
        return prev_count;
    }
    
    inline bool should_walk_from_root (SizeType prev_count, SizeType new_count)
    {
        SizeType rollover_bit = (prev_count ^ new_count) + 1;
        SizeType rollover_cost_bit = rollover_bit * rollover_bit;
        return rollover_cost_bit == 0 || rollover_cost_bit > m_level_bit;
    }
    
    inline void bubble_up_node (State st, Ref node, Ref parent, Link sibling, bool side)
    {
        Ref gparent;
        
        while (true) {
            gparent = ac(parent).parent.ref(st);
            if (gparent.isNull() || Compare::compareEntries(st, gparent, node) <= 0) {
                break;
            }
            
            bool next_side = parent.link() == ac(gparent).link[1];
            Link next_sibling = ac(gparent).link[!next_side];
            
            ac(gparent).link[side] = parent.link();
            ac(parent).parent = gparent.link();
            
            if (!(ac(gparent).link[!side] = sibling).isNull()) {
                ac(sibling.ref(st)).parent = gparent.link();
            }
            
            side = next_side;
            sibling = next_sibling;
            parent = gparent;
        }
        
        ac(node).link[side] = parent.link();
        ac(parent).parent = node.link();
        
        if (!(ac(node).link[!side] = sibling).isNull()) {
            ac(sibling.ref(st)).parent = node.link();
        }
        
        if (!(ac(node).parent = gparent.link()).isNull()) {
            ac(gparent).link[parent.link() == ac(gparent).link[1]] = node.link();
        } else {
            m_root = node.link();
        }
    }
    
    inline Ref check_for_bubble_down (State st, Ref node, Link child0, Link child1, bool *out_next_side)
    {
        Ref child = child0.ref(st);
        bool next_side = false;
        
        Ref child1_ref = child1.ref(st);
        if (!child1_ref.isNull() && Compare::compareEntries(st, child1_ref, child) < 0) {
            child = child1_ref;
            next_side = true;
        }
        
        if (child.isNull() || Compare::compareEntries(st, child, node) >= 0) {
            return Ref::null();
        }
        
        *out_next_side = next_side;
        return child;
    }
    
    inline void bubble_down_node_if_needed (State st, Ref node)
    {
        Link child0 = ac(node).link[0];
        Link child1 = ac(node).link[1];
        
        bool next_side;
        Ref child = check_for_bubble_down(st, node, child0, child1, &next_side);
        if (child.isNull()) {
            return;
        }
        
        Ref parent = ac(node).parent.ref(st);
        bool side = !parent.isNull() && node.link() == ac(parent).link[1];
        
        do_one_step_bubble_down(st, node, child, next_side, parent, side, child0, child1);
        
        connect_and_bubble_down_node(st, node, parent, side, child0, child1);
    }
    
    inline void do_one_step_bubble_down (State st, Ref node, Ref child, bool next_side,
                                         Ref &parent, bool &side, Link &child0, Link &child1)
    {
        Link other_child = next_side ? child0 : child1;
        
        child0 = ac(child).link[0];
        child1 = ac(child).link[1];
        
        if (!(ac(child).parent = parent.link()).isNull()) {
            ac(parent).link[side] = child.link();
        } else {
            m_root = child.link();
        }
        
        if (!(ac(child).link[!next_side] = other_child).isNull()) {
            ac(other_child.ref(st)).parent = child.link();
        }
        
        if (m_last == child.link()) {
            m_last = node.link();
        }
        
        parent = child;
        side = next_side;
    }
    
    inline void connect_and_bubble_down_node (State st, Ref node, Ref parent, bool side, Link child0, Link child1)
    {
        while (true) {
            bool next_side;
            Ref child = check_for_bubble_down(st, node, child0, child1, &next_side);
            if (child.isNull()) {
                break;
            }
            
            do_one_step_bubble_down(st, node, child, next_side, parent, side, child0, child1);
        }
        
        if (!(ac(node).parent = parent.link()).isNull()) {
            ac(parent).link[side] = node.link();
        } else {
            m_root = node.link();
        }
        
        if (!(ac(node).link[0] = child0).isNull()) {
            ac(child0.ref(st)).parent = node.link();
        }
        
        if (!(ac(node).link[1] = child1).isNull()) {
            ac(child1.ref(st)).parent = node.link();
        }
    }
    
    enum class AssertState {NoDepth, Lowest, LowestEnd};
    
    struct AssertData {
        AssertState state;
        int level;
        Link prev_leaf;
        SizeType count;
    };
    
    void assert_recurser (State st, Ref n, AssertData &ad, int level)
    {
        ad.count++;
        
        if (ac(n).link[0].isNull() && ac(n).link[1].isNull()) {
            if (ad.state == AssertState::NoDepth) {
                ad.state = AssertState::Lowest;
                ad.level = level;
            }
        } else {
            if (!ac(n).link[0].isNull()) {
                AMBRO_ASSERT_FORCE(Compare::compareEntries(st, n, ac(n).link[0].ref(st)) <= 0)
                AMBRO_ASSERT_FORCE(ac(ac(n).link[0].ref(st)).parent == n.link())
                assert_recurser(st, ac(n).link[0].ref(st), ad, level + 1);
            }
            if (!ac(n).link[1].isNull()) {
                AMBRO_ASSERT_FORCE(Compare::compareEntries(st, n, ac(n).link[1].ref(st)) <= 0)
                AMBRO_ASSERT_FORCE(ac(ac(n).link[1].ref(st)).parent == n.link())
                assert_recurser(st, ac(n).link[1].ref(st), ad, level + 1);
            }
        }
        
        AMBRO_ASSERT_FORCE(ad.state == AssertState::Lowest || ad.state == AssertState::LowestEnd)
        
        if (level < ad.level - 1) {
            AMBRO_ASSERT_FORCE(!ac(n).link[0].isNull() && !ac(n).link[1].isNull())
        }
        else if (level == ad.level - 1) {
            switch (ad.state) {
                case AssertState::Lowest:
                    if (ac(n).link[0].isNull()) {
                        ad.state = AssertState::LowestEnd;
                        AMBRO_ASSERT_FORCE(ac(n).link[1].isNull())
                        AMBRO_ASSERT_FORCE(ad.prev_leaf == m_last)
                    } else {
                        if (ac(n).link[1].isNull()) {
                            ad.state = AssertState::LowestEnd;
                            AMBRO_ASSERT_FORCE(ad.prev_leaf == m_last)
                        }
                    }
                    break;
                case AssertState::LowestEnd:
                    AMBRO_ASSERT_FORCE(ac(n).link[0].isNull() && ac(n).link[1].isNull())
                    break;
                default:
                    AMBRO_ASSERT(false);
            }
        }
        else if (level == ad.level) {
            AMBRO_ASSERT_FORCE(ad.state == AssertState::Lowest)
            AMBRO_ASSERT_FORCE(ac(n).link[0].isNull() && ac(n).link[1].isNull())
            ad.prev_leaf = n.link();
        }
        else {
            AMBRO_ASSERT_FORCE(false)
        }
    }
};

#include <aprinter/EndNamespace.h>

#endif
