// ----------------------------------------------------------------------------
// myClocksWithCrystals.c  ('FR6989 Launchpad)
//
// This routine sets up the Low Frequency crystal (LFXT) and high-freq
// internal clock source (DCO). Then configures ACLK, SMCLK, and MCLK:
//    ACLK  = 32KHz
//    SMCLK =  2MHz
//    MCLK  =  4MHz
// ----------------------------------------------------------------------------

//***** Header Files **********************************************************
#include <stdbool.h>
#include <driverlib.h>
#include "myClocks.h"


//***** Defines ***************************************************************
// See additional #defines in 'myClocks.h'
#define XT_TIMEOUT                     100000


//***** Global Variables ******************************************************
uint32_t myACLK  = 0;
uint32_t mySMCLK = 0;
uint32_t myMCLK  = 0;

uint8_t  returnValue = 0;
bool     bReturn     = STATUS_FAIL;


//***** initClocks ************************************************************
void initClocks(void) {

    //**************************************************************************
    // Configure Oscillators
    //**************************************************************************
    // Set the LFXT and HFXT crystal frequencies being used so that driverlib
    //   knows how fast they are (needed for the clock 'get' functions)
    CS_setExternalClockSource(
            LF_CRYSTAL_FREQUENCY_IN_HZ,
            HF_CRYSTAL_FREQUENCY_IN_HZ
    );

    // Verify if the default clock settings are as expected
    myACLK  = CS_getACLK();
    mySMCLK = CS_getSMCLK();
    myMCLK  = CS_getMCLK();

    // Initialize the LFXT crystal oscillator (using a timeout in case there is a problem with the crystal)
    // - This requires PJ.4 and PJ.5 pins to be connected (and configured) as "crystal" pins.
    // - Another alternative is to use the non-timeout function which "hangs" if LFXT isn't configured:
    //    CS_turnOnLFXT( CS_LFXT_DRIVE_0 );
    // - The "WithTimeout" function used here will always exit, even if LFXT fails to initialize.
    //   You must check to make sure LFXT was initialized properly... in a real application, you would
    //   usually replace the while(1) with a more useful error handling function.
    bReturn = CS_turnOnLFXTWithTimeout(
                  CS_LFXT_DRIVE_0,
                  XT_TIMEOUT
              );

    if ( bReturn == STATUS_FAIL )
    {
        while( 1 );
    }


//    // Initialize HFXT. Returns STATUS_SUCCESS if initializes successfully.
//    // The FR6989 Launchpad does not ship with HF crystal, so we've left it commented-out.
//     bReturn = CS_turnOnHFXTWithTimeout( 
//                   CS_HFXTDRIVE_4MHZ_8MHZ,
//                   XT_TIMEOUT
//               );
//
//     if ( bReturn == STATUS_FAIL )
//     {
//         while( 1 );
//     }

    // Set DCO to 4MHz
    CS_setDCOFreq(
            CS_DCORSEL_0,                                                       // Set Frequency range (DCOR)
            CS_DCOFSEL_3                                                        // Set Frequency (DCOF)
    );

    //**************************************************************************
    // Configure Clocks
    //**************************************************************************
    // Set ACLK to use LFXT as its oscillator source (32KHz)
    // With a 32KHz crystal and a divide by 1, ACLK should run at that rate
    CS_initClockSignal(
            CS_ACLK,                                                            // Clock you're configuring
            CS_LFXTCLK_SELECT,                                                  // Clock source
            CS_CLOCK_DIVIDER_1                                                  // Divide down clock source by this much
    );

    // Select LFXT as SMCLK oscillator source  ('FR6989 Launchpad does not ship with HFXT populated)
    // With DCO set at 4MHz, SMCLK is set for half that rate (2MHz)
    CS_initClockSignal( 
            CS_SMCLK,                                                           // Clock you're configuring
            CS_DCOCLK_SELECT,                                                   // Clock source
            CS_CLOCK_DIVIDER_2                                                  // Divide down clock source by this much
    );

    // Set MCLK to use DCO as its oscillator source (DCO was configured earlier in this function for 4MHz)
    CS_initClockSignal(
            CS_MCLK,                                                            // Clock you're configuring
            CS_DCOCLK_SELECT,                                                   // Clock source
            CS_CLOCK_DIVIDER_1                                                  // Divide down clock source by this much
    );

    // Verify that the modified clock settings are as expected
    myACLK  = CS_getACLK();
    mySMCLK = CS_getSMCLK();
    myMCLK  = CS_getMCLK();
}

