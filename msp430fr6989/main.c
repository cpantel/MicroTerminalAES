#include <msp430fr6989.h>
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
    PM5CTL0 = ENABLE_PINS;

    // setup leds
    P1DIR = BIT0;
    P9DIR = BIT7;
    P1OUT = 0x00;
    P9OUT = 0x00;

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


    // enable UART RXD interrupt
    UCA0IE = UCRXIE;
    _BIS_SR(GIE);

    while (1);
}

#pragma vector=USCI_A0_VECTOR
__interrupt void UART_ISR(void) {
       P9OUT ^= BIT7;
       if (UCA0RXBUF == 'a' ) {
           P1OUT = BIT0;
       } else {
           P1OUT = 0x00;
       }
       UCA0IFG = UCA0IFG & ~(UCRXIFG);

}
