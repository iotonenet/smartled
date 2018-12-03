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
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "systools.h"

static int print_status = 1;
static bool print_initialised = false;
static TaskHandle_t xPrintTask = NULL;

void print_task(void *pvParameter)
{
	while (1){
		LOG_INFO("============free heap size =%d bytes==========", esp_get_free_heap_size());
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}

void open_print_heap(void)
{
	LOG_INFO("open print heap .\n");
	if (!print_initialised)
	{
		xTaskCreate(&print_task, "print_task", 2048, NULL, 6, &xPrintTask);
		print_initialised = true;
	}
}

void close_print_heap(void)
{
	LOG_INFO("close led blink .\n");
	if (print_initialised)
	{
		if (xPrintTask)
		{
			vTaskDelete(xPrintTask);
		}
		print_initialised = false;
	}
}