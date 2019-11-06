#include "LED_display.h"
#include "spi.h"

// This array contains the hexadecimal character required to display the corresponding
// hexadecimal digit on the 7-segment display.
const unsigned char LEDDisplayCharacters[16] = {
		0x3f, // 0
		0x06, // 1
		0x5B, // 2
		0x4F, // 3
		0x66, // 4
		0x6D, // 5
		0x7D, // 6
		0x07, // 7
		0x7F, // 8
		0x67, // 9
		0x77, // A
		0x7C, // B
		0x39, // C
		0x5E, // D
		0x79, // E
		0x71  // F
};

void InitializeLEDDisplay(void)
{
    INIT_BLANK;
    TURN_OFF_XLAT;
    SET_BLANK_AS_OUTPUT;
    SET_XLAT_AS_OUTPUT;
}

void SetLEDDisplay(unsigned int DisplayValue)
{
    unsigned int singles;
    if(DisplayValue > 10){
        singles = 10;
    } else {
        singles = DisplayValue;
    }
    unsigned int tens = 0;
    while (singles > 9){
        singles -= 10;
        tens += 1;
    }
    SPISendByte(LEDDisplayCharacters[singles]);
    SPISendByte(LEDDisplayCharacters[tens]);
    TURN_ON_XLAT;
    TURN_OFF_XLAT;
}

