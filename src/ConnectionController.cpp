// 
// 
// 
#include "ConnectionController.h"
#include <Wifi.h>
#include <HTTPClient.h>

HTTPClient http;

const char* ssid = "CPD";
const char* password = "98849884";
byte bssid[] = { 0xc0, 0x3d, 0xd9, 0x07, 0x7f, 0x60 };

const char* host = "192.168.15.167";
const char* device = "ESP32 - Weather Station";
const int port = 8080;


ConnectionController::ConnectionController()
{
    //Set initial values for private vars
}

bool ConnectionController::connect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    // WiFi.begin(ssid, password, 11, bssid, true);

    delayfor(100);
    unsigned long startAttemptTime = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT) {
        delayfor(100);
    }

    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }
    return true;
}

bool ConnectionController::send_data(String csvData) {
    log_i("Sending data\n");

    bool result = false;

    delayfor(100);

    http.begin(host, port, "/api/weather-station");
    http.setTimeout(10000);

    delayfor(100);
    
    http.addHeader("content-type", "text/plain charset=utf-8");

    int httpCode = http.POST(csvData);

    delayfor(100);


    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
        result = true;
    }
    http.end();
    
    log_d("Response code: %d\n", httpCode);
    return result;
}

bool ConnectionController::check_connection(){
    return (WiFi.status() == WL_CONNECTED);
}

void ConnectionController::delayfor(long milliseconds) {
    long d;
    d = millis();

    while (millis() - d < milliseconds) {
        yield();
    }
}

void ConnectionController::stop_connections() {
    log_i("Stoping WiFi\n");
    WiFi.mode(WIFI_OFF);
}