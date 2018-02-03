/* Copyright 2018, Carlos Pantelides
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "sapi.h"

void show(char *dato) {
    static uint8_t col = 1;
    static uint8_t on = true;

    lcdGoToXY( col,1);

    lcdSendStringRaw(dato);
    ++col;
    if (col > 16) {
       col = 1;
    } 
}


int main(void){

   char dato[] = { 0x0,0x0 };

   boardConfig();

   lcdInit( 16, 2, 5, 8 );

   uartConfig( UART_232, 9600 );

   uartConfig( UART_USB, 9600 );

   lcdClear();

   lcdGoToXY( 1, 1 );

   while(1) {

      if ( uartReadByte( UART_USB, (uint8_t * )&dato[0] ) ){
         uartWriteByte( UART_232, dato[0] );
      }

      if(  uartReadByte( UART_232, (uint8_t * )&dato[0] ) ){
         show(dato);
         uartWriteByte( UART_USB, dato[0] );
      }
   }
   return 0 ;
}

