/**
 * @file
 * Common functions used throughout the stack.
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Simon Goldschmidt
 *
 */

#include "lwip/opt.h"
#include "lwip/def.h"

/**
 * These are reference implementations of the byte swapping functions.
 * Byte swapping is the second thing you would want to optimize. You will
 * need to port it to your architecture and in your cc.h:
 *
 * #define LWIP_PLATFORM_BYTESWAP 1
 * #define LWIP_PLATFORM_BSWAP16(x) <your_bswap16>
 * #define LWIP_PLATFORM_BSWAP32(x) <your_bswap32>
 *
 * Note ntohs() and ntohl() are merely references to the htonx counterparts.
 */

#if !LWIP_PLATFORM_BYTESWAP

u16_t lwip_bswap16(u16_t n)
{
  return ((n & 0xff) << 8) | ((n & 0xff00) >> 8);
}

u32_t lwip_bswap32(u32_t n)
{
  return ((n & 0xff)         << 24) |
         ((n & 0xff00)       << 8)  |
         ((n & 0xff0000UL)   >> 8)  |
         ((n & 0xff000000UL) >> 24);
}

#endif
