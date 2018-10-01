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
#include "esp_system.h"
#include "wifi_status.h"
#include "ble_status.h"
#include "onenet_status.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "blink.h"


#define BLINK_GPIO CONFIG_BLINK_GPIO

static bool wifi_blink_initialised = false;
static TaskHandle_t xWifiBlinkTask = NULL;

void blink_task(void *pvParameter)
{
//	LOG_INFO("init blink task .\n");
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
//    	LOG_INFO("loop for led .\n");
    	int led_status = get_ble_status() + get_wifi_status() + get_onenet_status();
    	switch (led_status) {
    		case 1 : {
    			gpio_set_level(BLINK_GPIO, 1);
    			vTaskDelay(1000 / portTICK_PERIOD_MS);
    			break;
    		}
    		case 2 : {
    			/* Blink on (output high) */
				gpio_set_level(BLINK_GPIO, 1);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
				/* Blink off (output low) */
    			gpio_set_level(BLINK_GPIO, 0);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
    			break;
    		}
    		case 3 : {
    			/* Blink on (output high) */
				gpio_set_level(BLINK_GPIO, 1);
				vTaskDelay(3000 / portTICK_PERIOD_MS);
				/* Blink off (output low) */
				gpio_set_level(BLINK_GPIO, 0);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
    			break;
    		}
    		case 6 : {
    			/* Blink on (output high) */
				gpio_set_level(BLINK_GPIO, 1);
				vTaskDelay(500 / portTICK_PERIOD_MS);
				/* Blink off (output low) */
    			gpio_set_level(BLINK_GPIO, 0);
				vTaskDelay(500 / portTICK_PERIOD_MS);
    			break;
    		}
    		case 7 : {
    			/* Blink on (output high) */
				gpio_set_level(BLINK_GPIO, 1);
				vTaskDelay(7000 / portTICK_PERIOD_MS);
				/* Blink off (output low) */
				gpio_set_level(BLINK_GPIO, 0);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
    			break;
    		}
    		case 0 :
    		case 4 :
    		case 5 :
    		default : {
    			/* Blink off (output low) */
				gpio_set_level(BLINK_GPIO, 0);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
    			break;
    		}
    	}
    }
}

void init_blink(void)
{
	if (!wifi_blink_initialised) {
		xTaskCreate(&blink_task, "blink_task", 2048, NULL, 6, &xWifiBlinkTask);
		wifi_blink_initialised = true;
	}
}

void destory_blink(void)
{
	if (wifi_blink_initialised) {
		if (xWifiBlinkTask) {
			vTaskDelete(xWifiBlinkTask);
		}
		gpio_set_level(BLINK_GPIO, 0);
		wifi_blink_initialised = false;
	}
}

