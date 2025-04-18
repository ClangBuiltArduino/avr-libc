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

#ifndef	__DOXYGEN

#include <avr/io.h>

#if	E2END && __AVR_ARCH__ > 1

#include <avr/eeprom.h>
#include "asmdef.h"
#include "eedef.h"

ENTRY	eeprom_write_byte
	mov	r18, r22

ENTRY	eeprom_write_r18

#if  __AVR_XMEGA__	/* --------------------------------------------	*/

# ifndef CCP_IOREG_gc
#  define CCP_IOREG_gc	0xD8	/* IO Register Protection	*/
# endif
# ifndef NVM_CMD_READ_EEPROM_gc
#  define NVM_CMD_READ_EEPROM_gc		0x06
# endif
# ifndef NVM_CMD_LOAD_EEPROM_BUFFER_gc
#  define NVM_CMD_LOAD_EEPROM_BUFFER_gc		0x33
# endif
# ifndef NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc
#  define NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc	0x35
# endif
# ifndef  NVM_CMD_ERASE_EEPROM_BUFFER_gc
#  define NVM_CMD_ERASE_EEPROM_BUFFER_gc	0x36
# endif

#if    ! defined (NVM_EEMAPEN_bm)
  ; Saving X register because it might contain source address of block
    push XL
    push XH
#endif

  ; Prepare base address of NVM.
	ldi	ZL, lo8(NVM_BASE)
	ldi	ZH, hi8(NVM_BASE)

  ; Wait until NVM is not busy.
1:	ldd	r19, Z + NVM_STATUS - NVM_BASE
	sbrc	r19, NVM_NVMBUSY_bp
	rjmp	1b

  ; It has to be noted that for some Xmega parts (Eg. Xmega E family) EEPROM
  ; is always memory mapped. So it is not possible to disable EEPROM mapping
  ; explicitly.
  ; The presence of NVM_EEMAPEN_bm macro (from the part header file) can be
  ; checked to find out whether the device supports enabling/disabling of
  ; EEPROM mapping. Absence of NVM_EEMAPEN_bm could be interpreted safely as
  ; EEPROM always memory mapped and explicit memory mapping of EEPROM is not
  ; required/invalid.
#if     defined (NVM_EEMAPEN_bm)
  ; Disable EEPROM mapping into data space.
	ldd	r19, Z + NVM_CTRLB - NVM_BASE
	andi	r19, ~NVM_EEMAPEN_bm
	std	Z + NVM_CTRLB - NVM_BASE, r19

  ; Check the clearance of EEPROM page buffer.
	ldd	r19, Z + NVM_STATUS - NVM_BASE
	sbrs	r19, NVM_EELOAD_bp
	rjmp	3f			; erase is not required

  ; Note that we have only four clock cycles to write to the CCP
  ; protected register NVM_CTRLA, after writing to CCP.  The 'ldi'
  ; instruction always takes one clock to execute and 'std' instruction takes
  ; two clock cycles.  We fall within the four cycles that the CCP leaves
  ; us to write the command execution start bit to the NVM_CTRLA
  ; register.  Note that r18 must be preserved until written to NVM_DATA0

  ; Issue EEPROM Buffer Erase:
	ldi	r19, NVM_CMD_ERASE_EEPROM_BUFFER_gc
	std	Z + NVM_CMD - NVM_BASE, r19
	ldi	r19, CCP_IOREG_gc
	out	CCP, r19
	ldi	r19, NVM_CMDEX_bm
	std	Z + NVM_CTRLA - NVM_BASE, r19

  ; Wait until NVM is not busy.
2:	ldd	r19, Z + NVM_STATUS - NVM_BASE
	sbrc	r19, NVM_NVMBUSY_bp
	rjmp	2b

  ; Issue EEPROM Buffer Load command.
3:	ldi	r19, NVM_CMD_LOAD_EEPROM_BUFFER_gc
	std	Z + NVM_CMD - NVM_BASE, r19

	std	Z + NVM_ADDR0 - NVM_BASE, addr_lo
	std	Z + NVM_ADDR1 - NVM_BASE, addr_hi
	std	Z + NVM_ADDR2 - NVM_BASE, __zero_reg__

	std	Z + NVM_DATA0 - NVM_BASE, r18
#else
  	movw 	XL, addr_lo
	subi	XL, lo8(-MAPPED_EEPROM_START)
	sbci	XH, hi8(-MAPPED_EEPROM_START)
	st	X, r18
#endif

  ; Issue EEPROM Erase & Write command.
#if defined(NVMCTRL_CTRLA)
	ldi	r18, CCP_SPM_gc
	out CCP, r18
	ldi	r18, NVMCTRL_CMD_PAGEERASEWRITE_gc
	std	Z + NVMCTRL_CTRLA - NVM_BASE, r18
#else
	ldi	r18, NVM_CMD_ERASE_WRITE_EEPROM_PAGE_gc
	std	Z + NVM_CMD - NVM_BASE, r18
	ldi	r18, CCP_IOREG_gc
	ldi	r19, NVM_CMDEX_bm
	out	CCP, r18
	std	Z + NVM_CTRLA - NVM_BASE, r19
#endif

  ; Increment address.
	adiw	addr_lo, 1

#if    ! defined (NVM_EEMAPEN_bm)
  ; Restoring X register
    pop XH
    pop XL
#endif

	ret

#else		/* ----------------------------------------------------	*/

1:	sbic	_SFR_IO_ADDR (EECR), EEWE
	rjmp	1b

# if	 defined (EEPM0) && defined (EEPM1)
	; Set programming mode: erase and write.
	out	_SFR_IO_ADDR (EECR), __zero_reg__
# elif	 defined (EEPM0) || defined (EEPM1)
#  error	/* Unknown EECR register.	*/
# endif

# ifdef	 EEARH
#  if	  E2END > 0xFF
	out	_SFR_IO_ADDR (EEARH), addr_hi
#  else
	; This is for chips like ATmega48: the EEAR8 bit must be cleaned.
	out	_SFR_IO_ADDR (EEARH), __zero_reg__
#  endif
# endif
	out	_SFR_IO_ADDR (EEARL), addr_lo
	out	_SFR_IO_ADDR (EEDR), r18
	in	__tmp_reg__, _SFR_IO_ADDR (SREG)
	cli
	sbi	_SFR_IO_ADDR (EECR), EEMWE
	sbi	_SFR_IO_ADDR (EECR), EEWE
	out	_SFR_IO_ADDR (SREG), __tmp_reg__
	adiw	addr_lo, 1
	ret

#endif		/* ----------------------------------------------------	*/

ENDFUNC

#endif	/* E2END && __AVR_ARCH__ > 1 */
#endif	/* !__DOXYGEN__ */
