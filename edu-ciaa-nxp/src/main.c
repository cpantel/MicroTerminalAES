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

const char emeChar[8] = {
   0b10001,
   0b11011,
   0b10101,
   0b10101,
   0b10101,
   0b10101,
   0b10101,
   0b10001
};


const char heartChar[8] = {
   0b00000,
   0b01010,
   0b11111,
   0b11111,
   0b01110,
   0b00100,
   0b00000,
   0b00000
};
const char iiiChar[8] = {
   0b10010,
   0b11110,
   0b01100,
   0b00000,
   0b01100,
   0b01100,
   0b01100,
   0b01100
};
const char hhhChar[8] = {
   0b10000,
   0b10010,
   0b10010,
   0b11111,
   0b10010,
   0b10010,
   0b10010,
   0b00010
};
  const char oooChar[8] = {
   0b00000,
   0b10111,
   0b11011,
   0b10101,
   0b10010,
   0b10001,
   0b10001,
   0b11111
}; 
const char lllChar[8] = {
   0b00010,
   0b00100,
   0b00100,
   0b01000,
   0b01000,
   0b10000,
   0b11111,
   0b00000
};
const char pppChar[8] = {
   0b11000,
   0b10100,
   0b10010,
   0b10100,
   0b11000,
   0b10000,
   0b10000,
   0b10000
};

// descripcion del la letra
const char aaaChar[8] = {
   0b00000,
   0b11110,
   0b10010,
   0b11110,
   0b10010,
   0b10010,
   0b00010,
   0b00010
};
void show(char *dato) {
    static uint8_t col = 2;
    static uint8_t on = true;

    lcdGoToXY( 1, 1 );
    if (on) {
       lcdData(0);
    } else {
       lcdSendStringRaw(" ");
    }
    on = ! on;
    lcdGoToXY( col,1);


// reemplazo de la letra

    if (*dato == 'M') {
       lcdData(1);
    } else  if (*dato == 'A') {
       lcdData(2);
    } else  if (*dato == 'I') {
       lcdData(3);
    } else  if (*dato == 'H') {
       lcdData(4) ;
    } else  if (*dato == 'O') {
       lcdData(5);
    } else  if (*dato == 'L') {
       lcdData(6);
    } else  if (*dato == 'P') {
       lcdData(7);

    } else {
       lcdSendStringRaw(dato);
    }

//    if ( condicion ) { aacion } else { accion  }

     ++col;
     if (col > 16) {
        col = 2;
        lcdGoToXY( 2, 1 );
     } 



}


int main(void){

   char dato[] = { 0x0,0x0 };

   boardConfig();

   lcdInit( 16, 2, 5, 8 );


   lcdCreateChar( 0, heartChar );

   lcdCreateChar( 1, emeChar );

   lcdCreateChar( 2, aaaChar );

   lcdCreateChar( 3, iiiChar );

   lcdCreateChar( 4, hhhChar );

   lcdCreateChar( 5, oooChar );

   lcdCreateChar( 6, lllChar );

   lcdCreateChar( 7, pppChar );


// creacion de la letra

   uartConfig( UART_USB, 9600 );

   lcdClear();

   lcdGoToXY( 1, 1 );

   lcdData(0);


   while(1) {
      if ( uartReadByte( UART_USB, (uint8_t * )&dato[0] ) ){
         uartWriteByte( UART_USB, dato[0] );
         show(dato);
      }


   }

   return 0 ;
}

