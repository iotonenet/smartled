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
#include "systools.h"

#define STORAGE_NAMESPACE "smart_storage"

void init_nvs()
{
	// Initialize NVS
	LOG_INFO("init nvs.");
	esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		LOG_ERROR("init nvs error.");
		ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
	LOG_INFO("init nvs done.");
}

char * read_str(const char* key)
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

void write_str(const char* key,const char* value)
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

int32_t read_i32(const char* key)
{
	int32_t ret = 0;
	nvs_handle my_handle;
	esp_err_t err = nvs_open(STORAGE_NAMESPACE, NVS_READONLY, &my_handle);
	if (err != ESP_OK) {
		;
	} else {
		err = nvs_get_i32(my_handle, key, &ret);
		switch (err) {
			case ESP_OK:
				break;
			case ESP_ERR_NVS_NOT_FOUND:
				printf("The value is not initialized yet!\n");
				break;
			default :
				printf("Error (%s) reading!\n", esp_err_to_name(err));
				break;
		}
	}
	// Close
	nvs_close(my_handle);
	printf("read int32 (%d) done!\n", ret);
	return ret;
}

/**
 * 往nvs中写一个int32
 */
void write_i32(const char* key,int32_t value)
{
	nvs_handle my_handle;
	esp_err_t err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
	if (err != ESP_OK) {
		;
	} else {
		err = nvs_set_i32(my_handle, key, value);
		if(err == ESP_OK){
			err = nvs_commit(my_handle);
		}
	}
	// Close
	nvs_close(my_handle);
}
