#ifndef PWM_H_
#define PWM_H_

#define TA0CCR1_DELTA 1
#define CALDCO_FREQUENCY CALDCO_16MHZ
#define CALBC1_FREQUENCY CALBC1_16MHZ
#define SMCLK_DIVIDE DIVS_0
#define TIMERA_CLOCK_DIVIDE ID_3
#define PWM_PERIOD 2000
#define inc_dec    200

/*
 * Frequency of Timer clock is 8MHz
 * Frequency of ISR is 1KHz (we want this number)
 * PWM Period is 2000
 *
 */

#endif /* PWM_H_ */
