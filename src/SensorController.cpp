// 
// 
// 

#include "SensorController.h"
#include "SparkFunBME280.h"
#include "SPIFFS.h"

BME280 BME280Sensor;

RTC_DATA_ATTR int pluviometerCnt = 0;
BME280_SensorMeasurements measurements;

SensorController::SensorController()
{
    //Set initial values for private vars
}

void SensorController::begin() {
    BME280Sensor.beginI2C();
    BME280Sensor.setFilter(IIR_FILTER);
    BME280Sensor.setStandbyTime(SAMPLING_FREQUENCY);

    BME280Sensor.setTempOverSample(TEMPERATURE_OVERSAMPLING);
    BME280Sensor.setPressureOverSample(HUMIDITY_OVERSAMPLING);
    BME280Sensor.setHumidityOverSample(PESSURE_OVERSAMPLING);

    BME280Sensor.setMode(MODE_NORMAL);
}

void SensorController::sleep(){
    log_i("Sensor to MODE_SLEEP\n");
    BME280Sensor.setMode(MODE_SLEEP);
}

void SensorController::get_weather_data(float weather_data[]) {
    log_i("Reading sensor data\n");

    while (BME280Sensor.isMeasuring()){
        Serial.println("Wainting for measurement to be ready...\n");
    };
    
    BME280Sensor.readAllMeasurements(&measurements);

    weather_data[0] = measurements.temperature;
    weather_data[1] = measurements.humidity;
    weather_data[2] = measurements.pressure;
    weather_data[3] = pluviometerCnt;

    clear_pluviometer_counter();

    log_d("%.2f,%.2f,%.2f,%.2f\n", weather_data[0], weather_data[1], weather_data[2], weather_data[3]);
}

void SensorController::save_pluviometer_data() {
    log_i("Increase pluviometer counter\n");
    pluviometerCnt++;
    log_d("Pluviometer counter: %d\n", pluviometerCnt);
}

void SensorController::clear_pluviometer_counter() {
    log_i("Reset pluviometer counter\n");
    pluviometerCnt = 0;
}

void SensorController::debug_weather_data() {
    unsigned long start = micros();
    while (BME280Sensor.isMeasuring()){
        Serial.println("Wainting for measurement to be ready...");
    };
    Serial.printf("Time waiting: %lu\n",micros() - start);
    start = micros();
    BME280Sensor.readAllMeasurements(&measurements);
    Serial.printf("Time for burst: %lu\n",micros() - start);
    Serial.printf("From Burst: %.2f,%.2f,%.2f\n", measurements.temperature, measurements.humidity, measurements.pressure);

    start = micros();
    float temp = BME280Sensor.readTempC();
    float humid = BME280Sensor.readFloatHumidity();
    float press = BME280Sensor.readFloatPressure();
    Serial.printf("Time for single: %lu\n",micros() - start);
    Serial.printf("From single: %.2f,%.2f,%.2f\n", temp, humid, press);
}
