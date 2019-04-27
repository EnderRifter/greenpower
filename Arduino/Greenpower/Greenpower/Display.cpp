//
//
//

#include "Display.h"

#include <Adafruit_GFX.h>

Display::Display()
{
	display_identifier = get_lcd_id(tft_display);
}

void Display::setup_display()
{
	// We reset the display and read its id
	tft_display.reset();
	display_identifier = tft_display.readID();

	// There is no need to change the id
	if (display_identifier == 0x9325 || display_identifier == 0x9328 || display_identifier == 0x4535 ||
		display_identifier == 0x7575 || display_identifier == 0x9595 || display_identifier == 0x4747 ||
		display_identifier == 0x8347 || display_identifier == 0x9341 || display_identifier == 0x7783 ||
		display_identifier == 0x8230 || display_identifier == 0x8357 || display_identifier == 0x7793 ||
		display_identifier == 0xB509 || display_identifier == 0x9486 || display_identifier == 0x9488)
	{
	}
	// Otherwise, the id needs to be changed.
	else if (display_identifier == 0x0101)
	{
		display_identifier = 0x9341;
	}
	else
	{
		display_identifier = 0x9486;
	}

	// We begin talking to the display with the correct settings.
	tft_display.begin(display_identifier);

	// We clear the screen and reset the position of the cursor.
	tft_display.fillScreen(BLACK);
	tft_display.setCursor(0, 0);
}

unsigned short Display::get_display_id() const
{
	return display_identifier;
}

void Display::write(char str[], const uint16_t x, const uint16_t y, const uint16_t colour)
{
	tft_display.setCursor(x, y);
	tft_display.setTextColor(colour);
	tft_display.println(str);
}

void lcd_debug(const Display& lcd_display)
{
	const uint16_t display_identifier = lcd_display.get_display_id();

	if (display_identifier == 0x9325)
	{
		Serial.println(F("Found ILI9325 LCD driver"));
	}
	else if (display_identifier == 0x9328)
	{
		Serial.println(F("Found ILI9328 LCD driver"));
	}
	else if (display_identifier == 0x4535)
	{
		Serial.println(F("Found LGDP4535 LCD driver"));
	}
	else if (display_identifier == 0x7575)
	{
		Serial.println(F("Found HX8347G LCD driver"));
	}
	else if (display_identifier == 0x9595)
	{
		Serial.println(F("Found HX8347-I LCD driver"));
	}
	else if (display_identifier == 0x4747)
	{
		Serial.println(F("Found HX8347-D LCD driver"));
	}
	else if (display_identifier == 0x8347)
	{
		Serial.println(F("Found HX8347-A LCD driver"));
	}
	else if (display_identifier == 0x9341)
	{
		Serial.println(F("Found ILI9341 LCD driver"));
	}
	else if (display_identifier == 0x7783)
	{
		Serial.println(F("Found ST7781 LCD driver"));
	}
	else if (display_identifier == 0x8230)
	{
		Serial.println(F("Found UC8230 LCD driver"));
	}
	else if (display_identifier == 0x8357)
	{
		Serial.println(F("Found HX8357D LCD driver"));
	}
	else if (display_identifier == 0x0101)
	{
		Serial.println(F("Found 0x9341 LCD driver"));
	}
	else if (display_identifier == 0x7793)
	{
		Serial.println(F("Found ST7793 LCD driver"));
	}
	else if (display_identifier == 0xB509)
	{
		Serial.println(F("Found R61509 LCD driver"));
	}
	else if (display_identifier == 0x9486)
	{
		Serial.println(F("Found ILI9486 LCD driver"));
	}
	else if (display_identifier == 0x9488)
	{
		Serial.println(F("Found ILI9488 LCD driver"));
	}
	else
	{
		Serial.print(F("Unknown LCD driver chip: "));
		Serial.println(display_identifier, HEX);
		Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
		Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
		Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
		Serial.println(F("If using the breakout board, it should NOT be #defined!"));
		Serial.println(F("Also if using the breakout, double-check that all wiring"));
		Serial.println(F("matches the tutorial."));
	}
}