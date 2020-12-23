// 
// 
// 

#include "SPIFFS.h"
#include "MemoryController.h"

typedef struct {
    float   Temp;
    float   Humi;
    int     Pres;
    int     Pluv;
} weatherReadings;

weatherReadings sensorData;

MemoryController::MemoryController()
{
    //Set initial values for private vars
}

void MemoryController::save(float weather_data[]) {
    log_i("Saving data to memory\n");
    File sensorDataFile = SPIFFS.open("/data", FILE_APPEND);

    sensorData.Temp = weather_data[0];
    sensorData.Humi = weather_data[1];
    sensorData.Pres = weather_data[2];
    sensorData.Pluv = weather_data[3];

    sensorDataFile.write((byte *)&sensorData, sizeof(sensorData));
    sensorDataFile.close();
}  

String MemoryController::get_data() {
    log_i("Reading memory\n");
    File sensorDataFile = SPIFFS.open("/data", FILE_READ);
    String CSVData = "";
    
    while(sensorDataFile.available()){
        sensorDataFile.read((byte *)&sensorData, sizeof(sensorData));
        CSVData.concat(String(sensorData.Temp) + "," + String(sensorData.Humi) + "," + String(sensorData.Pres) + "," + String(sensorData.Pluv) + "\n");
    }

    sensorDataFile.close();

    CSVData.trim();
    log_d("CSV Data Being send\n%s", CSVData.c_str());
    return CSVData;
}

void MemoryController::clear_data_file() {
    log_i("Data cleared\n");
    SPIFFS.remove("/data");
}

bool MemoryController::is_memory_full() {
    File sensorDataFile = SPIFFS.open("/data", FILE_READ);
    long dataSize = sensorDataFile.size();
    sensorDataFile.close();
    log_d("/data file size: %d bytes\n", dataSize);
    return (dataSize >= (sizeof(weatherReadings)*MAXIMUM_READINGS));
}

