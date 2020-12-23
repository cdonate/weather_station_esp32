/*
 Name:		WeatherStation.ino
 Created:	12/12/2020 2:26:41 PM
 Author:	Claudio
*/

#include <Arduino.h>
#include "SPIFFS.h"

// typedef struct {
//     float   Temp;
//     float   Humi;
//     float   Pluv;
// } weatherReadings;
// int tt = 5;
// File file;
 
// void setup() {
 
//   Serial.begin(115200);
//   randomSeed(analogRead(0));

//   unsigned long start = millis();

//   if (!SPIFFS.begin(true)) {
//     Serial.println("An Error has occurred while mounting SPIFFS");
//     return;
//   }


//   weatherReadings d;

//   SPIFFS.remove("/data");

//   File myFile = SPIFFS.open("/data", FILE_WRITE);
//   myFile.flush();// .write('');

//   for(int i = 0; i < 5; i++){
//     d.Humi = random(10);
//     d.Pluv = random(10, 20);
//     d.Temp = random(20, 30);
//     Serial.printf( "write: %.2f, %.2f, %.2f\n", d.Humi, d.Pluv, d.Temp);
//     myFile.write((byte *)&d, sizeof(d));
//     delay(1000);
//   }
//   myFile.close();

//   // for(int i = 0; i < 5; i++){
//   //   d.Humi = random(10);
//   //   d.Pluv = random(10, 20);
//   //   d.Temp = random(20, 30);
//   //   Serial.printf( "write: %.2f, %.2f, %.2f\n", d.Humi, d.Pluv, d.Temp);
//   //   myFile.write((byte *)&d, sizeof(d));
//   //   delay(1000);
//   // }
//   // myFile.close();
 
//   Serial.println((millis() - start));
// }
 
// void loop() {

//   weatherReadings t;

//   File myFile = SPIFFS.open("/data", FILE_READ);
//   // for(int i = 0; i < tt; i++){
//   while(myFile.available()){
//     // Serial.println(myFile.seek(i*sizeof(t), SeekCur));
//     Serial.println(myFile.position());
//     myFile.read((byte *)&t, sizeof(t));
//     Serial.printf( "read: %.2f, %.2f, %.2f\n", t.Humi, t.Pluv, t.Temp);
//     delay(1000);
//   }
//   myFile.close();

//   tt++;

//   File myFile2 = SPIFFS.open("/data", FILE_APPEND);

//   t.Humi = random(10);
//   t.Pluv = random(10, 20);
//   t.Temp = random(20, 30);
//   Serial.printf( "write: %.2f, %.2f, %.2f\n", t.Humi, t.Pluv, t.Temp);
//   myFile2.write((byte *)&t, sizeof(t));
//   myFile2.close();
// }

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

    // if (!SPIFFS.begin(true)) {
    //   Serial.println("An Error has occurred while mounting SPIFFS");
    //   return;
    // }    

    // weatherSensor.begin();
    delay(10);

    powerController.begin();
    powerController.boot_reason();
    delay(10);
}

void loop() {
    
    
    
    switch (powerController.get_boot_reason())
    {
        case RAIN_BOOT:
            // process_rain_boot();
            break;
        case NORMAL_BOOT:
            weatherSensor.begin();
            // weatherSensor.test();
            break;
        case TIMER_BOOT:
            // weatherSensor.test();
            weatherSensor.begin();
            weatherSensor.print_weather_data();
            // weatherSensor.test();
            // process_timer_boot();
            break;
        default:
            powerController.sleep();
            break;
    }
    
    powerController.sleep();
    //sleep(1);
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
    powerController.sleep();
}

void process_rain_boot() {
    weatherSensor.save_pluviometer_data();
    powerController.sleep();
}

bool send_data(String csvData){
    if (server.connect()) {
        return server.send_data(csvData);
    }
    return false;
}