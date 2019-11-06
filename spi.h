#ifndef USCI_SPI_H
#define USCI_SPI_H

#include <msp430.h>
#define READ_PORT_PIN(PORT,BIT,PIN) ((PORT & BIT) >> PIN) // Returns port pin value of 0 or 1.

// Note that P1.6 is being used as the PWM output from Timer A.

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * USCI B0 Master-Out-Slave-In (MOSI)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.7
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define USCIB0_MOSI_BIT					BIT7
#define USCIB0_MOSI_PORT				P1OUT
#define USCIB0_MOSI_DDR 				P1DIR
#define WRITE_LOGIC_1_TO_SLAVE			USCIB0_MOSI_PORT |= USCIB0_MOSI_BIT
#define WRITE_LOGIC_0_TO_SLAVE			USCIB0_MOSI_PORT &= ~USCIB0_MOSI_BIT
#define SET_USCIB0_MOSI_AS_AN_OUTPUT	USCIB0_MOSI_DDR |= USCIB0_MOSI_BIT

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Slave Clock for GPIO Flash Memory Board
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * GPIO      :  P1.5
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define SPI_SCK_BIT					BIT5
#define SPI_SCK_PORT				P1OUT // SPI Slave Clock output
#define SPI_SCK_DDR					P1DIR // SPI Slave Clock direction
#define SET_SPI_SCK_AS_AN_OUTPUT	SPI_SCK_DDR |= SPI_SCK_BIT
#define INITIALIZE_SPI_SCK			SPI_SCK_PORT &= ~SPI_SCK_BIT
#define TOGGLE_SPI_SCK				SPI_SCK_PORT ^= SPI_SCK_BIT

/*
 * This function initializes all hardware and port pins to support SPI.
 */
void InitializeSPI();

/*
 * This function sends the byte, SendValue, using SPI.
 */
void SPISendByte(unsigned char SendValue);

#endif
