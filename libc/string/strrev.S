/* Copyright (c) 2002, 2007 Reiner Patommel
   Copyright (c) 2007  Dmitry Xmelkov
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

/*
   strrev.S
   Reverse a string

   Contributors:
     Created by Reiner Patommel
*/

#if !defined(__DOXYGEN__)

#include "asmdef.h"

#define str_hi r25
#define str_lo r24
#define ltemp  r23
#define rtemp  r22

ENTRY _U(strrev)
	X_movw	XL, str_lo	; X is start of string
	X_movw	ZL, str_lo	; Z becomes end of string
  ; find end of string
1:	mov	rtemp, ltemp	; to obtain right nonzero character
	ld	ltemp, Z+
	tst	ltemp
	brne	1b
	X_sbiw	ZL, 2		; to last nonzero byte
	rjmp	3f
  ; swap bytes
2:	ld	ltemp, X
	st	X+, rtemp
	st	Z, ltemp
	ld	rtemp, -Z
3:	cp	XL, ZL
	cpc	XH, ZH
	brlo	2b

	ret

ENDFUNC

#endif /* not __DOXYGEN__ */
