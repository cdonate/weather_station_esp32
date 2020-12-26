// WeatherSensor.h

#ifndef _SENSORCONTROLLER_h
#define _SENSORCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif

#define SENSOR_ADDR 0x76

// #define TEMPERATURE_OVERSAMPLING 1
// #define HUMIDITY_OVERSAMPLING 1
// #define PESSURE_OVERSAMPLING 1

// #define FILTER_OFF 0
// #define SAMPLING_FREQUENCY 5 // 1000ms

#define TEMPERATURE_OVERSAMPLING 4
#define HUMIDITY_OVERSAMPLING 4
#define PESSURE_OVERSAMPLING 4

#define FILTER_OFF 0
#define IIR_FILTER 2
#define SAMPLING_FREQUENCY 6 // 10ms

#define SPI_DISABLED 0


class SensorController {

public:
	SensorController();

	//Public Functions
	void begin(void);
	void get_weather_data(float[]);
	void save_pluviometer_data();
	void sleep();
	void debug_weather_data();
	//Public Variables

private:
	void clear_pluviometer_counter();
	//Private Functions

	//Private Variables

};

