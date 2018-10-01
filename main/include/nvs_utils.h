/*
 * nvs_utils.h
 * read or write value from nvs
 *
 *  Created on: Sep 28, 2018
 *      Author: songfei
 */

#ifndef MAIN_INCLUDE_NVS_UTILS_H_
#define MAIN_INCLUDE_NVS_UTILS_H_

/**
 * 从nvs中读取字符串
 */
char * read_str(const char* key);

/**
 * 往nvs中写入一个字符串
 */
void write_str(const char* key,const char* value);

/**
 * 从nvs中读取int32
 */
int32_t read_i32(const char* key);

/**
 * 往nvs中写一个int32
 */
void write_i32(const char* key,int32_t value);
#endif /* MAIN_INCLUDE_NVS_UTILS_H_ */
