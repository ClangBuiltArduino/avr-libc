/* Copyright (c) 2010  Joerg Wunsch
   Copyright (c) 2013  Frederic Nadeau
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

/* Test the various CRC algorithms.
   Part 5:  8-bit CCITT-CRC, x^8 + x^2 + x + 1 (0xE0) */

#include <stdint.h>
#include <stdlib.h>

#ifdef	__AVR__
# include <util/crc16.h>
#else  /* host computer */

static uint8_t
_crc8_ccitt_update (uint8_t inCrc, uint8_t inData)
{
    uint8_t   i;
	uint8_t   data;

	data = inCrc ^ inData;

    for ( i = 0; i < 8; i++ )
	{
    	if (( data & 0x80 ) != 0 )
    	{
    		data <<= 1;
        	data ^= 0x07;
    	}
    	else
    	{
    		data <<= 1;
    	}
    }
    return data;
}

#endif  /* AVR */

/* LTC6802-1 test vector (including CRC) */
const char message[] = "\xE1\x04\x02\x20\x6C\x6C\x62";
const size_t mlen = 7;

#include <stdio.h>

int main(void)
{
    uint8_t crc = 0;
    uint8_t i;

    for (i = 0; i < mlen; i++)
        crc = _crc8_ccitt_update(crc, message[i]);
    if (crc != 0) return __LINE__;

    return 0;
}

