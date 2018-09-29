/*
 * nvs_utils.c
 *
 *  Created on: Sep 28, 2018
 *      Author: songfei
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "nvs_utils.h"

#define STORAGE_NAMESPACE "storage"

char * read_str(char * key)
{
	char* ret = NULL;
	nvs_handle my_handle;
	esp_err_t err = nvs_open(STORAGE_NAMESPACE, NVS_READONLY, &my_handle);
	if (err != ESP_OK) {
		;
	} else {
		size_t required_size;
		err = nvs_get_str(my_handle, key, NULL, &required_size);
		if(err == ESP_OK){
			ret = malloc(required_size);
			err = nvs_get_str(my_handle, key, ret, &required_size);
			switch (err) {
				case ESP_OK:
					break;
				case ESP_ERR_NVS_NOT_FOUND:
				default :
					ret = NULL;
					break;
			}
		}
	}
	// Close
	nvs_close(my_handle);
	return ret;
}

void write_str(char * key,char * value)
{
	nvs_handle my_handle;
	esp_err_t err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK) {
		;
	} else {
		err = nvs_set_str(my_handle, key, value);
		if(err == ESP_OK){
			err = nvs_commit(my_handle);
		}
	}
	// Close
	nvs_close(my_handle);
}
