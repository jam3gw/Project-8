#ifndef LED_DISPLAY_H_
#define LED_DISPLAY_H_

#include <msp430.h>

// Function Prototypes
void InitializeLEDDisplay(void);
/*
 * This function configures and initializes all of the pins associated with the 7-segment displays.
 */

void SetLEDDisplay(unsigned int DisplayValue);
/*
 * Given as an input DisplayValue, this function will determine the correct digits to display in the
 * two 7-segment displays, and then use this information to send the appropriate information to the
 * LED display drivers.
 */

#define BLANK_PORT      P1OUT
#define BLANK_BIT       BIT4
#define BLANK_DDR       P1DIR
#define SET_BLANK_AS_OUTPUT     BLANK_DDR |= BLANK_BIT
#define INIT_BLANK      BLANK_PORT &= ~BLANK_BIT  //Turn it off

#define XLAT_PORT      P2OUT
#define XLAT_BIT       BIT0
#define XLAT_DDR       P2DIR
#define SET_XLAT_AS_OUTPUT     XLAT_DDR |= XLAT_BIT
#define TURN_ON_XLAT      XLAT_PORT |= XLAT_BIT //Active High
#define TURN_OFF_XLAT      XLAT_PORT &= ~XLAT_BIT //Active High

#endif /* LED_DISPLAY_H_ */
