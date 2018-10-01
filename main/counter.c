/*
 * counter.c
 *
 *  Created on: Sep 30, 2018
 *      Author: songfei
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "nvs_utils.h"
#include "counter.h"

#define RESTART_COUNTER "restart_counter"

void increase(void)
{
	int32_t current = read_i32(RESTART_COUNTER);
	write_i32(RESTART_COUNTER,++current);
}

int32_t get_count()
{
	return read_i32(RESTART_COUNTER);
}
