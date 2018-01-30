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
       static int pos = 1;

       P9OUT ^= BIT7;
       uint8_t l = UCA0RXBUF;
       if (l == 'A' ) {
           P1OUT = BIT0;
           myLCD_showSymbol(LCD_TOGGLE, LCD_HRT, 0);
       } else {
           P1OUT = 0x00;
       }
       myLCD_showChar(l,pos);
       ++pos;
       if (pos > 6) pos = 1;



       UCA0TXBUF = l;
       UCA0IFG = UCA0IFG & ~(UCRXIFG);

}
