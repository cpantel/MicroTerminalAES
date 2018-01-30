/*
 * myClocks.h
 *
 */

#ifndef LCD_MYCLOCKS_H_
#define LCD_MYCLOCKS_H_

//***** Prototypes ************************************************************
void initClocks(void);

//***** Defines ***************************************************************
#define LF_CRYSTAL_FREQUENCY_IN_HZ     32768
#define HF_CRYSTAL_FREQUENCY_IN_HZ     0                                        // FR6989 Launchpad does not ship with HF Crystal populated

#define myMCLK_FREQUENCY_IN_HZ         4000000
#define mySMCLK_FREQUENCY_IN_HZ        2000000
#define myACLK_FREQUENCY_IN_HZ         32768


#endif /* LCD_MYCLOCKS_H_ */

