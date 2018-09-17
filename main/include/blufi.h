/*
 * blufi.h
 *
 *  Created on: Sep 15, 2018
 *      Author: songfei
 */
#pragma once

#define LOG_TAG "SMART_LED"
#define LOG_INFO(fmt, ...)   ESP_LOGI(LOG_TAG, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)  ESP_LOGE(LOG_TAG, fmt, ##__VA_ARGS__)

void blufi_dh_negotiate_data_handler(uint8_t *data, int len, uint8_t **output_data, int *output_len, bool *need_free);
int blufi_aes_encrypt(uint8_t iv8, uint8_t *crypt_data, int crypt_len);
int blufi_aes_decrypt(uint8_t iv8, uint8_t *crypt_data, int crypt_len);
uint16_t blufi_crc_checksum(uint8_t iv8, uint8_t *data, int len);

int blufi_security_init(void);
void blufi_security_deinit(void);
