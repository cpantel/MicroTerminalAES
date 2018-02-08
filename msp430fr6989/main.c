#include <msp430fr6989.h>

#include <driverlib.h>
#include "myGpio.h"
#include "myClocks.h"
#include "myLcd.h"


#define ENABLE_PINS     0xFFFE

#define UART_CLK_SEL  0x0080
#define BR0_FOR_9600  0x34
#define BR1_FOR_9600  0x00
#define CLK_MOD       0x4911


char buffer[] = "01234567890ABCDEF";

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    initGPIO();
    initClocks();
    myLCD_init();

    // select clock signals
    CSCTL0 = 0xA500;
    CSCTL1 = 0x0046;
    CSCTL2 = 0x0133;
    CSCTL3 = 0x0000;

    // assign_pins_to_uart
    P4SEL1  = 0x00;
    P4SEL0  = BIT3 | BIT2;

    // use_9600_baud
    UCA0CTLW0  = UCSWRST;
    UCA0CTLW0  = UCA0CTLW0 | UART_CLK_SEL;
    UCA0BR0    = BR0_FOR_9600;
    UCA0BR1    = BR1_FOR_9600;
    UCA0MCTLW  = CLK_MOD;
    UCA0CTLW0  = UCA0CTLW0 & (~UCSWRST);


    myLCD_showChar('A',1);
    myLCD_showChar('E',2);
    myLCD_showChar('S',3);
    myLCD_showChar('R',4);
    myLCD_showChar('U',5);
    myLCD_showChar('N',6);

    myLCD_showSymbol(LCD_UPDATE,LCD_BRACKETS,0);


    // enable UART RXD interrupt
    UCA0IE = UCRXIE | UCTXIE;
    UCA0IFG = UCA0IFG & ~(UCTXIFG);

    _BIS_SR(GIE);

    while (1);
}



#pragma vector=USCI_A0_VECTOR
__interrupt void UART_ISR(void) {
   static int lcdIdx = 1;
   static int bufferIdx = 0;

   if ( UCA0IFG & UCRXIFG ) {
       P9OUT ^= BIT7;

       uint8_t charRead = UCA0RXBUF;

       myLCD_showChar(charRead,lcdIdx );

       buffer[bufferIdx]=charRead;

       ++lcdIdx;
       ++bufferIdx;

       if (lcdIdx > 6) lcdIdx = 1;

       if (bufferIdx > 0) myLCD_showSymbol(LCD_UPDATE,LCD_B1,0);
       if (bufferIdx > 3) myLCD_showSymbol(LCD_UPDATE,LCD_B2,0);
       if (bufferIdx > 6) myLCD_showSymbol(LCD_UPDATE,LCD_B3,0);
       if (bufferIdx > 9) myLCD_showSymbol(LCD_UPDATE,LCD_B4,0);
       if (bufferIdx > 12) myLCD_showSymbol(LCD_UPDATE,LCD_B5,0);
       if (bufferIdx > 14) myLCD_showSymbol(LCD_UPDATE,LCD_B6,0);


       if ( bufferIdx > 15) {
           myLCD_showSymbol(LCD_UPDATE, LCD_TX, 0);


           myLCD_showSymbol(LCD_CLEAR,LCD_B1,0);
           myLCD_showSymbol(LCD_CLEAR,LCD_B2,0);
           myLCD_showSymbol(LCD_CLEAR,LCD_B3,0);
           myLCD_showSymbol(LCD_CLEAR,LCD_B4,0);
           myLCD_showSymbol(LCD_CLEAR,LCD_B5,0);
           myLCD_showSymbol(LCD_CLEAR,LCD_B6,0);
           myLCD_showSymbol(LCD_CLEAR, LCD_TX, 0);

           UCA0TXBUF = buffer[0];
           bufferIdx=1;


       }

       UCA0IFG = UCA0IFG & ~(UCRXIFG);

    }

    if ( UCA0IFG & UCTXIFG ) {
           P1OUT ^= BIT0;
           UCA0IFG = UCA0IFG & ~(UCTXIFG);
           if (bufferIdx < 16) {
               UCA0TXBUF = buffer[bufferIdx];
              ++bufferIdx;
           } else {
               bufferIdx = 0;
           }



    }


}
