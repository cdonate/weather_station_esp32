// 
// 
// 

#include "PowerController.h"
#include "ConnectionController.h"

ConnectionController connection;


RTC_DATA_ATTR int bootReason = 0;


PowerController::PowerController()
{
    //Set initial values for private vars
}

void PowerController::begin() {
    btStop();
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 0);
    esp_sleep_enable_timer_wakeup(SLEEP_INTERVAL);
}

void PowerController::sleep() {
    log_i("Going to sleep\n");
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_ON);
    connection.stop_connections();
    
    esp_deep_sleep_start();
}

int PowerController::get_boot_reason() {
    return bootReason;
}

void PowerController::boot_reason() {
    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason)
    {
        case ESP_SLEEP_WAKEUP_EXT0:
            log_i("Wakeup caused by rain input\n");
            bootReason = RAIN_BOOT;
            break;
        case ESP_SLEEP_WAKEUP_TIMER:
            log_i("Wakeup caused by timer\n");
            bootReason = TIMER_BOOT;
            break;
        default:
            log_i("Normal boot\n");
            bootReason = NORMAL_BOOT;
            break;
    }
    
}