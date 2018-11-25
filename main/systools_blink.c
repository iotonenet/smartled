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

static int led_status = 0;

static int led_status_sc = 0;
static int led_status_wifi = 0;
static int led_status_mqtt = 0;

static bool blink_initialised = false;
static bool is_blinker = false;
static TaskHandle_t xBlinkTask = NULL;

void blink_task(void *pvParameter)
{
	//	LOG_INFO("init blink task .\n");
	gpio_pad_select_gpio(BLINK_GPIO);
	/* Set the GPIO as a push/pull output */
	gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
	while (1)
	{
		led_status = led_status_sc + led_status_wifi + led_status_mqtt;
		// LOG_INFO("led status:%d.",led_status);
		switch (led_status)
		{
		case 1:
		{
			// 快闪500ms
			if (is_blinker)
			{
				gpio_set_level(BLINK_GPIO, 0);
				vTaskDelay(500 / portTICK_PERIOD_MS);
			}
			else
			{
				gpio_set_level(BLINK_GPIO, 1);
				vTaskDelay(500 / portTICK_PERIOD_MS);
			}
			break;
		}
		case 2:
		case 3:
		{
			// 常亮
			gpio_set_level(BLINK_GPIO, 1);
			vTaskDelay(500 / portTICK_PERIOD_MS);
			break;
		}
		case 4:
		case 6:
		case 7:
		{
			// 中闪1s，正常工作中
			if (is_blinker)
			{
				gpio_set_level(BLINK_GPIO, 0);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
			}
			else
			{
				gpio_set_level(BLINK_GPIO, 1);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
			}
			break;
		}
		case 5:
		{
			// 理论不该存在，肯定something wrong了.
			LOG_ERROR("something wrong,led status value is 5.");
			break;
		}
		case 0:
		default:
		{
			// 慢闪
			// 中闪1s，正常工作中
			if (is_blinker)
			{
				gpio_set_level(BLINK_GPIO, 0);
				vTaskDelay(3000 / portTICK_PERIOD_MS);
			}
			else
			{
				gpio_set_level(BLINK_GPIO, 1);
				vTaskDelay(3000 / portTICK_PERIOD_MS);
			}
			break;
		}
		}
		is_blinker = !is_blinker;
	}
}

void open_blink(void)
{
	LOG_INFO("open led blink .\n");
	if (!blink_initialised)
	{
		xTaskCreate(&blink_task, "blink_task", 2048, NULL, 6, &xBlinkTask);
		blink_initialised = true;
	}
}

void close_blink(void)
{
	LOG_INFO("close led blink .\n");
	if (blink_initialised)
	{
		if (xBlinkTask)
		{
			vTaskDelete(xBlinkTask);
		}
		gpio_set_level(BLINK_GPIO, 0);
		blink_initialised = false;
	}
}

void switch_led(int led_code, int value)
{
	LOG_INFO("switch led for %d,value:%d.\n", led_code, value);
	if (value != 1)
	{
		value = 0;
	}
	// smart config status 1;
	// wifi status 2;
	// mqtt status 4;
	switch (led_code)
	{
	case CODE_LED_SC:
	{
		if (led_status_sc != value * 1)
		{
			led_status_sc = value * 1;
		}
		break;
	}
	case CODE_LED_WIFI:
	{
		if (led_status_wifi != value * 2)
		{
			led_status_wifi = value * 2;
		}
		break;
	}
	case CODE_LED_MQTT:
	{
		if (led_status_mqtt != value * 4)
		{
			led_status_mqtt = value * 4;
		}
		break;
	}
	default:
	{
		LOG_ERROR("some thing wrong,switch led code is not supported.");
		break;
	}
	}
}

/**
 * led标示以后状态，smart config状态1；wifi连接状态2；mqtt状态4;
 * 所以led_status取值含义如下：
 * 0：所有状态都是0；LED慢闪（3s）
 * 1：smart config状态是1，其他的是0；LED快闪（500ms）表示等待配网；
 * 2：wifi连接状态是1，其他的是0；LED常亮，表示配网成功，但mqtt未连接；
 * 3：smart config和wifi连接状态是1，其他的是0；LED常亮，表示配网成功，但mqtt未连接；
 * 4：mqtt状态是1，其他的是0；这种情况不存在；LED中闪；表示mqtt连接成功，设备正常工作中；
 * 5：smart config和mqtt状态是1，其他的是0；但这种情况不存在；
 * 6：wifi和mqtt状态是1，其他的是0；LED中闪；表示mqtt连接成功，设备正常工作中；
 * 7：smart config、wifi、mqtt状态是1；LED中闪；表示mqtt连接成功，设备正常工作中；
 */