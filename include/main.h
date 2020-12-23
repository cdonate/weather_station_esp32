#ifndef _MAIN_h
#define _MAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif

void process_timer_boot();
void process_rain_boot();
bool send_data(String);