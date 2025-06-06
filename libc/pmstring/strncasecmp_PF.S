/* Copyright (c) 2006, Carlos Lamas

   based on libc/pmstring/strncasecmp_P.S which is
   Copyright (c) 2002, Reiner Patommel

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

#if !defined(__AVR_TINY__)

#include "asmdef.h"

#define s1_b1 r25
#define s1_b0 r24
#define s2_b3 r23
#define s2_b2 r22
#define s2_b1 r21
#define s2_b0 r20
#define len_b1 r19
#define len_b0 r18

#define tmp s2_b0

#define ret_b1 r25
#define ret_b0 r24

#if !defined(__DOXYGEN__)

ENTRY _U(strncasecmp_PF)

	X_movw	ZL, s2_b0
	LPM_R0_ZPLUS_INIT s2_b2
	X_movw	XL, s1_b0

.L_strncasecmp_PF_loop:

	subi	len_b0, lo8(1)
	sbci	len_b1, hi8(1)
	brcs	.L_strncasecmp_PF_equal
	ld	ret_b0, X+		; load *s1
	cpi	ret_b0, 'A'		; if ret_b0 in [A-Z]...
	brlt	1f
	cpi	ret_b0, 'Z'+1
	brge	1f
	subi	ret_b0, 'A'-'a'		; ...then tolower().
1:	LPM_R0_ZPLUS_NEXT s2_b2		; load *s2
	mov	tmp, r0			; copy of *s2 to tmp
	cpi	tmp, 'A'		; if tmp in [A-Z]...
	brlt	2f
	cpi	tmp, 'Z'+1
	brge	2f
	subi	tmp, 'A'-'a'		; ...then tolower().

2:	sub	ret_b0, tmp
	brne	.L_strncasecmp_PF_done
	tst	r0
	brne	.L_strncasecmp_PF_loop

.L_strncasecmp_PF_equal:

	sub	ret_b0, ret_b0

.L_strncasecmp_PF_done:
; ret_hi = SREG.C ? 0xFF : 0

	sbc	ret_b1, ret_b1
	LPM_R0_ZPLUS_FINI
	ret

ENDFUNC

#endif /* not __DOXYGEN__ */

#endif /* !defined(__AVR_TINY__) */
