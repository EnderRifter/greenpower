// miscellaneous.h

#ifndef _MISCELLANEOUS_h
#define _MISCELLANEOUS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <Streaming.h>

#include "CarOS.h"

// wiring with UNO or Mega2560:
//--------------POWER Pins--------------------------------
//   5V  connects to DC 5V
//   GND connects to Ground
//   3V3 do not need to connect(NC)
//--------------LCD Display Pins--------------------------
//   LCD_RD   connects to Analog pin A0
//   LCD_WR   connects to Analog pin A1
//   LCD_RS   connects to Analog pin A2
//   LCD_CS   connects to Analog pin A3
//   LCD_RST  connects to Analog pin A4
//   LCD_D0   connects to digital pin 8
//   LCD_D1   connects to digital pin 9
//   LCD_D2   connects to digital pin 2
//   LCD_D3   connects to digital pin 3
//   LCD_D4   connects to digital pin 4
//   LCD_D5   connects to digital pin 5
//   LCD_D6   connects to digital pin 6
//   LCD_D7   connects to digital pin 7
//--------------SD-card fuction Pins ----------------------
//This Connection Only for UNO, Do not support Mega2560
//because they use different Hardware-SPI Pins
//SD_SS    connects to digital pin 10
//SD_DI    connects to digital pin 11
//SD_DO    connects to digital pin 12
//SD_SCK   connects to digital pin 13

// Can alternately just connect to Arduinos reset pin. Set to Analog pin 4.
constexpr uint8_t LCD_RESET = A4;

// Chip Select goes to Analog pin 3.
constexpr uint8_t LCD_CS = A3;

// Command/Data goes to Analog pin 2.
constexpr uint8_t LCD_CD = A2;

// LCD Write goes to Analog pin 1.
constexpr uint8_t LCD_WR = A1;

// LCD RS - identical to LCD_CD
constexpr uint8_t LCD_RS = LCD_CD;

// LCD Read goes to Analog pin 0.
constexpr uint8_t LCD_RD = A0;

// Represents the colour black as a 16-bit value.
constexpr uint16_t BLACK = 0x0000;

// Represents the colour blue as a 16-bit value.
constexpr uint16_t BLUE = 0x001F;

// Represents the colour red as a 16-bit value.
constexpr uint16_t RED = 0xF800;

// Represents the colour green as a 16-bit value.
constexpr uint16_t GREEN = 0x07E0;

// Represents the colour cyan as a 16-bit value.
constexpr uint16_t CYAN = 0x07FF;

// Represents the colour magenta as a 16-bit value.
constexpr uint16_t MAGENTA = 0xF81F;

// Represents the colour yellow as a 16-bit value.
constexpr uint16_t YELLOW = 0xFFE0;

// Represents the colour white as a 16-bit value.
constexpr uint16_t WHITE = 0xFFFF;

// Gets the ID for our display's processing chip. Inlined for performance reasons.
inline uint16_t get_lcd_id(MCUFRIEND_kbv* lcd_screen)
{
	return lcd_screen->readID();
}

// Represents a 2 dimensional vector.
template <typename T>
struct vec2
{
	// The x component of the vector.
	T x;

	// The y component of the vector.
	T y;
};

// Represents a display that can be written to or drawn on.
class display
{
private:
	// The display that we will be drawing to.
	MCUFRIEND_kbv* tft_display = nullptr;

	// The ID for our display's processing chip.
	uint16_t display_identifier = 0x9486;

	// Holds the size of the display (x = width, y = height).
	vec2<int> display_size{ 0, 0 };

	// The default size for any text written to the screen. Rendered text size in pixels
	// is calculated via the following equation: pixel_size = font_size * 10.
	static const uint16_t TEXT_SIZE = 2;

	// The default background colour for the screen.
	static const uint16_t BG_COLOUR = BLACK;

	// The default foreground colour for the screen.
	static const uint16_t FG_COLOUR = WHITE;

protected:
	// Returns the number of pixels that the given string message will take up on the display
	// at the given font size. Inlined for performance reasons.
	static uint16_t string_size_in_pixels(const char* str, const int font_size)
	{
		// The font size in pixels can be found via: pixel_size = font_size * 10
		return strlen(str) * font_size * 10;
	}

	// Called to move the display's cursor to the correct position on the screen, and set the
	// appropriate colour for drawing text. Inlined for performance reasons.
	void start_draw_text(const int x_pos, const int y_pos, const uint16_t text_colour, const int text_size) const
	{
		tft_display->setCursor(x_pos, y_pos);
		tft_display->setTextSize(text_size);
		tft_display->setTextColor(text_colour);
	}

public:
	// Initialises a new instance of the Display class.
	explicit display(MCUFRIEND_kbv* lcd_display);

	// Sets the display up ready for writing or drawing.
	void setup_display();

	// Gets the identifier for the processing chip of the display.
	uint16_t get_display_id() const
	{
		return display_identifier;
	}

	// Gets the size of the display.
	vec2<int> get_display_size() const
	{
		return display_size;
	}

	// Gets the width of a character with the given font size.
	static int get_font_width(const int font_size = TEXT_SIZE)
	{
		return font_size * 10;
	}

	// Gets the height of a character with the given font size.
	static int get_font_height(const int font_size = TEXT_SIZE)
	{
		return font_size * 10;
	}

	// Writes the given string message to the display, starting at the given (x, y) cursor position.
	// Writes the message in the default colour (white) and default font size.
	void write(const char* str, const int x, const int y)
	{
		write(str, x, y, FG_COLOUR, TEXT_SIZE);
	}

	// Writes the given string message to the display, starting at the given (x, y) cursor position.
	// Writes the message in the given 16-bit colour, and with the given font size.
	void write(const char* str, int x, int y, uint16_t colour, int size);

	// Writes the given printable object to the display, starting at the given (x, y) cursor position.
	// Writes the message in the given 16-bit colour, and with the given font size.
	void write_printable(Printable* printable, int x, int y, uint16_t colour, int size);

	// Draws a vertical line of the given height, 1 pixel wide, starting at the given (x, y) cursor position.
	// Draws the line in the default colour (white).
	void draw_vertical_line(const int x, const int y, const int height)
	{
		draw_vertical_line(x, y, height, 1, FG_COLOUR);
	}

	// Draws a vertical line of the given height, 1 pixel wide, starting at the given (x, y) cursor position.
	// Draws the line in the given 16-bit colour.
	void draw_vertical_line(const int x, const int y, const int height, const uint16_t colour)
	{
		draw_vertical_line(x, y, height, 1, colour);
	}

	// Draws a vertical line of the given height, of the given thickness, starting at the given (x, y) cursor position.
	// Draws the line in the given 16-bit colour.
	void draw_vertical_line(int x, int y, int height, int thickness, uint16_t colour);

	// Draws a horizontal line of the given width, 1 pixel high, starting at the given (x, y) cursor position.
	// Draws the line in the default colour (white).
	void draw_horizontal_line(const int x, const int y, const int width)
	{
		draw_horizontal_line(x, y, width, 1, FG_COLOUR);
	}

	// Draws a horizontal line of the given width, 1 pixel high, starting at the given (x, y) cursor position.
	// Draws the line in the given 16-bit colour.
	void draw_horizontal_line(const int x, const int y, const int width, const uint16_t colour)
	{
		draw_horizontal_line(x, y, width, 1, colour);
	}

	// Draws a horizontal line of the given width, of the given thickness, starting at the given (x, y) cursor position.
	// Draws the line in the given 16-bit colour.
	void draw_horizontal_line(int x, int y, int width, int thickness, uint16_t colour);

	// Draws a filled rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// Draws the rectangle in the default colour (white).
	void draw_filled_rectangle(const uint16_t x, const uint16_t y, const uint16_t width, const int height)
	{
		draw_filled_rectangle(x, y, width, height, FG_COLOUR);
	}

	// Draws a filled rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// Draws the rectangle in the given 16-bit colour.
	void draw_filled_rectangle(int x, int y, int width, int height, uint16_t colour);

	// Draws a hollow rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// All lines that make up the rectangle (i.e. the left and right vertical line and the top and bottom horizontal line)
	// will be 1 pixel thick. Draws the rectangle in the default colour (white).
	void draw_hollow_rectangle(const int x, const int y, const int width, const int height)
	{
		draw_hollow_rectangle(x, y, width, height, FG_COLOUR);
	}

	// Draws a hollow rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// All lines that make up the rectangle (i.e. the left and right vertical line and the top and bottom horizontal line)
	// will be 1 pixel thick. Draws the rectangle in the given 16-bit colour.
	void draw_hollow_rectangle(int x, int y, int width, int height, uint16_t colour);

	// Draws a hollow rectangle, of the given width and height, starting at the given (x, y) cursor position.
	// All lines that make up the rectangle (i.e. the left and right vertical line and the top and bottom horizontal line)
	// will be of the given thickness (in pixels). Draws the rectangle in the given 16-bit colour.
	void draw_hollow_rectangle(int x, int y, int width, int height, int thickness, uint16_t colour);

	// Draws a pixel at the given (x, y) cursor position in the default colour (white).
	void draw_pixel(const int x, const int y)
	{
		draw_pixel(x, y, FG_COLOUR);
	}

	// Draws a pixel at the given (x, y) cursor position in the given 16-bit colour.
	void draw_pixel(int x, int y, uint16_t colour);

	// Sets up the MCUFRIEND_kvb lcd given, and returns the id in use by the lcd screen.
	friend uint16_t lcd_setup(MCUFRIEND_kbv* lcd_display);

	// Logs debug information about the given LCD screen to the serial connection.
	friend void lcd_debug(Print& print_stream, const display& lcd_display);
};

// Holds options for a pid controller.
// Reference: https://en.wikipedia.org/wiki/PID_controller
struct pid_options
{
public:
	// The target value for the pid controllers output, given input.
	double pid_setpoint = 0.0;

	// A reference to a double value holding the input (feedback) to the pid controller.
	double& pid_input_ref;

	// A reference to a double value holding the output from the pid controller.
	double& pid_output_ref;

	// Proportional gain - controls the sensitivity to deviations from the setpoint. The higher the
	// proportional gain, the larger the change in the output for a given change in the error value;
	// the pid controller will be more sensitive to any deviation from the setpoint.
	double kp = 0.1;

	// Integral gain - controls the accumulated error that should have been corrected previously. The larger
	// the integral term the faster the movement towards the setpoint. However care must be taken since
	// the integral term responds to previously accumulated error, it can overshoot the setpoint if the
	// integral gain is too large.
	double ki = 0.3;

	// Derivative gain - controls settling time (damping) and system stability. The larger the derivative
	// gain the longer it takes for the system to settle but the more stable it is (errors are damped more).
	// The smaller the value the more sensitive the system is to changes.
	double kd = 0.001;

	/*
	 * pid.SetMode(AUTOMATIC);
	 * pid.SetSampleTime(20); // sample time is in milliseconds
	 * pid.SetOutputLimits(0, 1000); // motor controller takes an input in this range
	 */
};

#endif
