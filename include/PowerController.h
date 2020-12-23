// SleepManager.h

#ifndef _SLEEPMANAGER_h
#define _SLEEPMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define NORMAL_BOOT 0
#define TIMER_BOOT 1
#define RAIN_BOOT 2

#define INTERRUPT_PIN 5
#define SLEEP_INTERVAL (1UL * 1UL * 1000000ULL)

class PowerController {

public:
	PowerController();

	//Public Functions
	void begin();
	void sleep();
	void set_sleep_timer_in_minutes(int);
	void boot_reason();
	int get_boot_reason();
	//Public Variables

private:
	//Private Functions

	//Private Variables
};

#endif

