#pragma once

#include <esp_log.h>
#define LOG_TAG "SMART_LED"
#define LOG_INFO(fmt, ...)   ESP_LOGI(LOG_TAG, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)  ESP_LOGE(LOG_TAG, fmt, ##__VA_ARGS__)