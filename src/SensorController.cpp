// 
// 
// 

#include "SensorController.h"
#include "SparkFunBME280.h"
#include "SPIFFS.h"

BME280 BME280Sensor;
// HTU21D HTU21DSensor;

RTC_DATA_ATTR int pluviometerCnt = 0;

SensorController::SensorController()
{
    //Set initial values for private vars
}

void SensorController::begin() {
    // BME280Sensor.setI2CAddress(SENSOR_ADDR);

    BME280Sensor.beginI2C();

    BME280Sensor.setFilter(FILTER_OFF);
    BME280Sensor.setStandbyTime(SAMPLING_FREQUENCY);

    BME280Sensor.setTempOverSample(TEMPERATURE_OVERSAMPLING);
    BME280Sensor.setPressureOverSample(HUMIDITY_OVERSAMPLING);
    BME280Sensor.setHumidityOverSample(PESSURE_OVERSAMPLING);
    BME280Sensor.setMode(MODE_SLEEP);
}

void SensorController::get_weather_data(float weather_data[]) {
    log_i("Reading sensor data\n");
    
    float temp = BME280Sensor.readTempC();// HTU21DSensor.readTemperature();
    float humd = BME280Sensor.readFloatHumidity(); //HTU21DSensor.readHumidity();
    float pres = BME280Sensor.readFloatPressure();
    float pluv = pluviometerCnt;

    weather_data[0] = temp;
    weather_data[1] = humd;
    weather_data[2] = pres;
    weather_data[3] = pluv;

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


void SensorController::print_weather_data() {
    // Serial.printf("Reading sensor data\n");
    // BME280Sensor.beginI2C();
    // BME280Sensor.setFilter(2);
    // BME280Sensor.setMode(MODE_FORCED);

    Serial.printf("%.2f,%.2f,%.2f\n", BME280Sensor.readTempC(), BME280Sensor.readFloatHumidity(), BME280Sensor.readFloatPressure());
}

void SensorController::test(){
    Serial.printf("Config: %d\n",BME280Sensor.readRegister(BME280_CONFIG_REG));
    Serial.printf("Mode: %d\n",BME280Sensor.getMode());
}