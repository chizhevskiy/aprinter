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

#ifndef APRINTER_STATIC_INTERFACE_H
#define APRINTER_STATIC_INTERFACE_H

#include <utility>

/**
 * Provides a compile-time interface mechanism which
 * allows calling only the interface methods, which are
 * dispatched statically not as virtual functions.
 * 
 * An example of an interface definition and use:
 * 
 * @code
 * APRINTER_STATIC_INTERFACE(MyInterface) {
 *     APRINTER_IFACE_FUNC(bool, Foo, (int x, int y))
 *     APRINTER_IFACE_FUNC(void, Bar, (bool z))
 * };
 * 
 * struct MyClass : public MyInterface<MyClass> {
 *     bool Foo (int x, int y) { return false; }
 *     void Bar (bool z) {}
 * };
 * 
 * template <typename Impl>
 * void UseInterface(MyInterface<Impl> &iface) {
 *     bool ret = iface.Foo(1, 2);
 *     iface.Bar(true);
 * }
 * 
 * MyClass myclass;
 * UseInterface(myclass);
 * @endcode
 * 
 * The implementation is such that the interface class will
 * contain functions which forward to the correspondign functions
 * in the implementing class. The arguments of these wrapper
 * functions are variadic and are forwarded using std::forward.
 * 
 * This macro can also be used for forward declarations,
 * in this case it must be followed by a semicolon.
 */
#define APRINTER_STATIC_INTERFACE(IfaceName) \
template <typename APrinter_iface_impl_type> \
struct IfaceName

/**
 * Use this to define interface functions in an interface defined
 * using APRINTER_STATIC_INTERFACE.
 */
#define APRINTER_IFACE_FUNC(RetType, FuncName, Args) \
template <typename... APrinter_iface_TArgs> \
inline RetType FuncName (APrinter_iface_TArgs && ... args) { \
    static constexpr RetType (APrinter_iface_impl_type::*ptr) Args = &APrinter_iface_impl_type::FuncName; \
    return ((static_cast<APrinter_iface_impl_type *>(this))->*ptr)(std::forward<APrinter_iface_TArgs>(args)...); \
}

#endif
