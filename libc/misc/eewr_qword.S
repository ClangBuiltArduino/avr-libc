/* Copyright (c) 2009  Dmitry Xmelkov
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
   POSSIBILITY OF SUCH DAMAGE.	*/

#ifndef	__DOXYGEN__

#include <avr/io.h>

#if	E2END && __AVR_ARCH__ > 1

#ifdef AVR_TINY
#error AVR_TINY has no EEPROM
#endif

#include <avr/eeprom.h>
#include "asmdef.h"
#include "eedef.h"

/* void eeprom_write_qword (uint64_t *addr, uint64 val);
 */

ENTRY	eeprom_write_qword
;;; No ENTRY for [long] double here because this file must not depend
;;; on -m[long-]double=.  This is because avr/devices/<mcu>/Makefile.am
;;; is just copying the main variant to the [long-]double<bits> folders.

    push    r19                 ; val[3]
    push    r18                 ; val[2]
    mov     r18, r16            ; val[0]
    XCALL   eeprom_write_r18
    mov     r18, r17            ; val[1]
    XCALL   eeprom_write_r18
    pop     r18                 ; val[2]
    XCALL   eeprom_write_r18
    pop     r18                 ; val[3]
    XCALL   eeprom_write_r18
    mov     r18, r20            ; val[4]
    XCALL   eeprom_write_r18
    mov     r18, r21            ; val[5]
    XCALL   eeprom_write_r18
    XJMP    eeprom_write_word   ; val[6], val[7]

ENDFUNC

#endif	/* E2END && __AVR_ARCH__ > 1 */
#endif	/* !__DOXYGEN__ */
