// ----------------------------------------------------------------------------
// myGpio.c  ('FR6989 Launchpad)
// ----------------------------------------------------------------------------

#include <driverlib.h>
#include "myGpio.h"

#define RED_ON              0x0001      // Enable and turn on the red LED
#define RED_OFF             0xFFFE      // Turn off the red LED
#define GREEN_ON			0x0080		// Enable and turn on the green LED
#define GREEN_OFF			0xFF7F		// Turn off the green LED
#define DEVELOPMENT         0x5A80      // Stop the watchdog timer
#define ENABLE_PINS         0xFFFE      // Required to use inputs and outputs
#define BUTTON1				0x0002		// P1.1 is button 1
#define BUTTON2				0x0004		// P1.2 is button 2


//*****************************************************************************
// Initialize GPIO
//*****************************************************************************
void initGPIO(void)
{

	P1DIR |= RED_ON;					// Red LED pin will be an output
    P1OUT &= RED_OFF;					// Start with red LED off

    P9DIR |= GREEN_ON;					// Green LED pin will be an output
    P9OUT &= GREEN_OFF;					// Start with green LED off

    PM5CTL0 = ENABLE_PINS;               // Enable to turn on LEDs

	P1OUT = P1OUT|BUTTON1;				// Set P1.1 as input with pull-up
	P1REN = P1REN|BUTTON1;				// resistor (for push button 1)

	P1OUT = P1OUT|BUTTON2;				// Set P1.2 as input with pull-up
	P1REN = P1REN|BUTTON2;				// resistor (for push button 2)

    // Set LFXT (low freq crystal pins) to crystal input (rather than GPIO)
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_PJ,
            GPIO_PIN4 +              	// LFXIN  on PJ.4
            GPIO_PIN5 ,             	// LFXOUT on PJ.5
            GPIO_PRIMARY_MODULE_FUNCTION
    );
}
