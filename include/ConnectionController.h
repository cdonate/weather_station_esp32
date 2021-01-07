// WifiServer.h

#ifndef _CONNECTIONCONTROLLER_h
#define _CONNECTIONCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#define WIFI_TIMEOUT 20000 // 20 seconds in milliseconds

class ConnectionController {

public:
	ConnectionController();

	//Public Functions
	bool check_connection(void);
	bool connect(void);
	bool send_data(String);
	void stop_connections();
	//Public Variables

private:
	void delayfor(long);
	//Private Functions

	//Private Variables

};