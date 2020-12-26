/*
 Name:		WeatherStation.ino
 Created:	12/12/2020 2:26:41 PM
 Author:	Claudio
*/

#include <Arduino.h>
#include "SPIFFS.h"
#include "main.h"
#include "ConnectionController.h"
#include "MemoryController.h"
#include "PowerController.h"
#include "SensorController.h"

ConnectionController server;
MemoryController flashMemory;
SensorController weatherSensor;
PowerController powerController;

float weather_data[4];

void setup() {
    Serial.begin(115200);
    delay(10);

    if (!SPIFFS.begin(true)) {
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }    

    weatherSensor.begin();
    delay(10);

    powerController.begin();
    powerController.boot_reason();
    delay(10);
}

void loop() {
    switch (powerController.get_boot_reason())
    {
        case RAIN_BOOT:
            process_rain_boot();
            break;
        case NORMAL_BOOT:
        case TIMER_BOOT:
            process_timer_boot();
            break;
        default:
            powerController.sleep();
            break;
    }
    
    powerController.sleep();
}

void process_timer_boot() {
    weatherSensor.get_weather_data(weather_data);
    flashMemory.save(weather_data);

    if (flashMemory.is_memory_full()) {
        String csvData = flashMemory.get_data();
        if (send_data(csvData)) {
            flashMemory.clear_data_file();
        }
    }
}

void process_rain_boot() {
    weatherSensor.save_pluviometer_data();
}

bool send_data(String csvData){
    if (server.connect()) {
        return server.send_data(csvData);
    }
    return false;
}