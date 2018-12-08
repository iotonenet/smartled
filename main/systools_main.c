/*
 * blink.c
 *
 *  Created on: Sep 15, 2018
 *      Author: songfei
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#include "systools.h"

void init_systools(void)
{
	// nvs init
	init_nvs();
	// reboot increase
	reboot_increase();
	// 打开led
	open_blink();
	// 打开print heap
	// open_print_heap();
    esp_log_level_set("*", ESP_LOG_DEBUG);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_DEBUG);
    esp_log_level_set("TRANSPORT_TCP", ESP_LOG_DEBUG);
    esp_log_level_set("TRANSPORT_SSL", ESP_LOG_DEBUG);
    esp_log_level_set("TRANSPORT", ESP_LOG_DEBUG);
    esp_log_level_set("OUTBOX", ESP_LOG_DEBUG);

}