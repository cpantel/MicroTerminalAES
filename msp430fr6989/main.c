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

    // enable UART RXD interrupt
    UCA0IE = UCRXIE;
    _BIS_SR(GIE);

    while (1);
}



#pragma vector=USCI_A0_VECTOR
__interrupt void UART_ISR(void) {
       static int lcdIdx = 1;
       static int bufferIdx = 0;


       P9OUT ^= BIT7;

       uint8_t charRead = UCA0RXBUF;

       myLCD_showSymbol(LCD_UPDATE, LCD_RX, 0);

       myLCD_showChar(charRead,lcdIdx );

       buffer[bufferIdx]=charRead;

       ++lcdIdx;
       ++bufferIdx;

       if (lcdIdx > 6) lcdIdx = 1;

       if ( bufferIdx > 15) {
           for (bufferIdx = 0; bufferIdx < 16 ; ++bufferIdx) {
               UCA0TXBUF = buffer[bufferIdx];
               //UCA0IFG = UCA0IFG & ( ~UCTXCPTIFG);
               int delay = 0;
               for (delay = 0; delay < 30000; ++delay);
               myLCD_showSymbol(LCD_TOGGLE, LCD_TX, 0);

           }
           bufferIdx = 0;

       }

       UCA0IFG = UCA0IFG & ~(UCRXIFG);

       myLCD_showSymbol(LCD_CLEAR, LCD_RX, 0);

}
