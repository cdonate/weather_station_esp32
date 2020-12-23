#ifndef _MEMORYCONTROLLER_h
#define _MEMORYCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define MAXIMUM_READINGS 4 // Send data to wifi every 60 minutes. 1 read every 15 minutes. 60 / 15 = 4

class MemoryController {

public:
	MemoryController();

	void save(float[]);
	void clear_data_file();
	String get_data();
	bool is_memory_full();

private:

};

#endif