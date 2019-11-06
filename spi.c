#include "spi.h"

void InitializeSPI()
{	
	SET_USCIB0_MOSI_AS_AN_OUTPUT;
	INITIALIZE_SPI_SCK;
	SET_SPI_SCK_AS_AN_OUTPUT;
}

void SPISendByte(unsigned char SendValue)
{
	unsigned short k;
	unsigned char LocalSendValue;

	LocalSendValue = SendValue;

	for (k = 0; k < 8; k++){
		
		// Assign a value to the MOSI based on the value of the MSB.
		if (LocalSendValue & 0x80) {
			WRITE_LOGIC_1_TO_SLAVE;
		}
		else {
			WRITE_LOGIC_0_TO_SLAVE;
		}
		
		// Left-shift local copy of data to send.
		LocalSendValue <<= 1;

		// Toggle SPI Clock: (HIGH XOR 1) -> LOW, and (LOW XOR 1) -> HIGH
		TOGGLE_SPI_SCK; TOGGLE_SPI_SCK; 
	}

}



