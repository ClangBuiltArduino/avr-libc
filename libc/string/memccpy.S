/* Copyright (c) 2002, 2007 Marek Michalkiewicz
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

#if !defined(__DOXYGEN__)

#include "asmdef.h"

TINY_WEAK_ALIAS _U(memccpy_P) _U(memccpy)

#define dest_hi r25
#define dest_lo r24
#define src_hi r23
#define src_lo r22
#define val_lo r20
#define len_hi r19
#define len_lo r18

#define ret_hi r25
#define ret_lo r24

#if defined(Lprogmem) && !defined(__AVR_TINY__)
# define memccpy    memccpy_P
# define LOAD	    X_lpm
#else
# define LOAD	    ld
#endif

ENTRY memccpy
#ifdef __AVR_TINY__
        ;; r18/r19 are callee-saved.
	push	r18
	push	r19
	;; len is passed on the stack.
	in	ZL, SPL_IO_ADDR
	in	ZH, SPH_IO_ADDR
	X_adiw 	ZL, 1 + 4	; 4 pushed (RET-address and r18/19).
	ld	r18, Z+
	ld	r19, Z+
#endif /* AVRrc */

	X_movw	ZL, src_lo
	X_movw	XL, dest_lo
.L_memccpy_loop:
	subi	len_lo, lo8(1)
	sbci	len_hi, hi8(1)
	brcs	.L_memccpy_notfound
	LOAD	__tmp_reg__, Z+
	st	X+, __tmp_reg__
	cp	__tmp_reg__, val_lo
	brne	.L_memccpy_loop
	X_movw	ret_lo, XL
#ifndef __AVR_TINY__
	ret
.L_memccpy_notfound:
	clr	ret_lo
	clr	ret_hi
	ret
#else /* AVRrc */
	rjmp	.L_epilogue
.L_memccpy_notfound:
	clr	ret_lo
	clr	ret_hi
.L_epilogue:
	pop	r19
	pop	r18
	ret
#endif /* AVRrc */

ENDFUNC
#endif /* not __DOXYGEN__ */
