/* Copyright (c) 2007  Dmitry Xmelkov
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

#ifndef	__DOXYGEN__

#include "asmdef.h"

TINY_WEAK_ALIAS _U(strspn_P) _U(strspn)

#define str_lo	r24
#define str_hi	r25
#define acc_lo	r22
#define acc_hi	r23

#define chs	r21	/* char from s[]	*/

/* This realization is compact, but is not very fast: an accept string
   is not cashed.	*/

ENTRY _U(strspn)
	X_movw	XL, str_lo
  ; get next symbol from s[]
1:	ld	chs, X+		; *s++
	tst	chs
	breq	3f
  ; check an occurrence
	X_movw	ZL, acc_lo
2:	ld	__tmp_reg__, Z+
	cp	__tmp_reg__, chs
	cpse	__tmp_reg__, __zero_reg__
	brne	2b
	breq	1b		; branch if chs is present in accept[]
  ; end of scanning: chs is not found or end of s[] is reached
  ; Return: X - 1 - str == X + ~str
3:	com	str_lo
	com	str_hi
	add	str_lo, XL
	adc	str_hi, XH
	ret

ENDFUNC

#endif	/* !__DOXYGEN__ */
