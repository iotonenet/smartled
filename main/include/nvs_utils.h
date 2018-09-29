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
char * read_str(char * key);

/**
 * 往nvs中写入一个字符串
 */
void write_str(char * key,char * value);

#endif /* MAIN_INCLUDE_NVS_UTILS_H_ */
