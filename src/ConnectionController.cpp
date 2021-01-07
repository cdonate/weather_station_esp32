// 
// 
// 
#include "ConnectionController.h"
#include <Wifi.h>
#include <HTTPClient.h>

#define IOT_ID 1

HTTPClient http;

const char* ssid = "CPD";
const char* password = "98849884";
byte bssid[] = { 0xc0, 0x3d, 0xd9, 0x07, 0x7f, 0x60 };

const char* host = "192.168.15.200";
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

    char url[20];
    snprintf(url, sizeof(url), "/api/iot/%d/weather", IOT_ID);
    
    bool result = false;

    delayfor(100);

    http.setTimeout(10000);
    http.begin(host, port, url);

    delayfor(100);
    
    http.addHeader("content-type", "text/csv");

    int httpCode = http.POST(csvData);

    http.end();

    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_NO_CONTENT) {
        result = true;
    }
    
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