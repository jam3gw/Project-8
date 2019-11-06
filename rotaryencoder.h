#ifndef ROTARYENCODER_H_
#define ROTARYENCODER_H_

#include <msp430.h>

#define ROTARY_ENCODER_BOUNCE_TIME_MAX 5

// Function Prototypes
void InitializeRotaryEncoderPortPins(void);
/*
 *  * This function configures and initializes all of the pins associated with the rotary encoder.
 */

#define OUT_A_PORT      P2IN
#define OUT_A_BIT       BIT4
#define OUT_A_DDR       P2DIR
#define SET_OUT_A_AS_INPUT      OUT_A_DDR &= ~OUT_A_BIT
#define INIT_OUT_A          OUT_A_PORT |= OUT_A_BIT

#define OUT_B_PORT      P2IN
#define OUT_B_BIT       BIT3
#define OUT_B_DDR       P2DIR
#define SET_OUT_B_AS_INPUT      OUT_B_DDR &= ~OUT_B_BIT
#define INIT_OUT_B          OUT_B_PORT |= OUT_B_BIT

#endif /* ROTARYENCODER_H_ */
