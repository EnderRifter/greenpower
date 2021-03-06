// Car.h

#ifndef _CAR_h
#define _CAR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Button.h"
#include "ButtonFunctions.h"
#include "Display.h"
#include "Greenpower.h"

// Total amount of energy in the battery when fully charged (E=I*V*dt).
constexpr int BATTERY_CAPACITY = 3400;

// The minimum reading for the throttle controlling pin.
constexpr int THROTTLE_MIN = 0;

// The maximum reading for the throttle controlling pin.
constexpr  int THROTTLE_MAX = 1023;

// The maximum reading for the speed controller.
constexpr int SPEED_CONTROLLER_MAX = 4000;

// Stores the possible modes that the car can be in.
enum class car_mode
{
	// The car is currently idle and conserving battery power.
	idle,

	// The car is currently in race mode and balancing speed and battery life.
	race,

	// The car is currently in overtake mode and prioritising performance over battery life.
	overtake,
};

// Stores the current state of the car.
class car_state
{
private:
	// The maximum value for the car's throttle, when not in overtake mode.
	const int THROTTLE_CAP = 255;

	// The maximum value for the speed controller, when not in overtake mode.
	const int SPEED_CONTROLLER_CAP = 255;

	// The reccomended value for the car's throttle.
	int reccomended_throttle = 30;

	// The current value for the car's throttle.
	int throttle = reccomended_throttle;

	// The current value for the speed controller.
	int speed_controller = 0;

	// The current amount of energy in the battery (E=I*V*dt). Initialised as the battery's capacity.
	float battery_level = BATTERY_CAPACITY;

	// The current battery percentage, between 0 and 1.
	float battery_percentage = 1;

	// Whether the car is in race mode.
	bool in_race_mode = false;

	// Whether the car is in overtake mode.
	bool in_overtake_mode = false;

	// The display we will be writing to and drawing on to show the cars internal state.
	display lcd_display{ &tft_display };

	// Increments a given variable by 1 whenever the ButtonAdd1 pin (pin 23) is high.
	button<int> increment_by1{ nullptr, pins::button_add1, &increment_variable_1, &null_func };

	// Increments a given variable by 10 whenever the ButtonAdd10 pin (pin 24) is high.
	button<int> increment_by10{ nullptr, pins::button_add10, &increment_variable_10, &null_func };

	// Decrements a given variable by 1 whenever the ButtonTake1 pin (pin 25) is high.
	button<int> decrement_by1{ nullptr, pins::button_take1, &decrement_variable_1, &null_func };

	// Decrements a given variable by 10 whenever the ButtonTake10 pin (pin 26) is high.
	button<int> decrement_by10{ nullptr, pins::button_take10, &decrement_variable_10, &null_func };

	// Array of all incrementation buttons that will be in use.
	button<int>* incrementation_buttons[4] = { &increment_by1, &increment_by10, &decrement_by1, &decrement_by10 };

	// Sets or resets the race mode flag if the race button is pressed or not.
	button<bool> race_button{ &in_race_mode, pins::button_race_mode, &set_bool, &reset_bool };

	// Sets or resets the overtake mode flag if the overtake button is pressed or not.
	button<bool> overtake_button{ &in_overtake_mode, pins::button_race_mode, &set_bool, &reset_bool };

	// Array of all mode buttons that will be in use.
	button<bool>* mode_buttons[2]{ &race_button, &overtake_button };

public:
	// Initialises a new instance of the CarState class.
	car_state() = default;

	// Updates all the buttons states.
	void update_buttons() const;

	// Returns the current mode of the car.
	inline car_mode get_car_mode() const;

	// Updates the car's internal state.
	void next_tick(unsigned long delta_time_ms);

	// Updates the screen with the car's current internal state.
	void update_screen();
};

#endif
