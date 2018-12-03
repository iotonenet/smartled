/**
 * @author Fick Song
 * @date 2018.11.14
 * 系统工具;
 * 控制系统LED提示灯
 * 控制系统在线升级FOTA
 * nvs utils
 * reboot counter
 */
#pragma once
#include "stdint.h"
#include "common.h"

// blink begin
// led for smart config
#define CODE_LED_SC 1
// led for wifi connection
#define CODE_LED_WIFI 2
// led for mqtt connection
#define CODE_LED_MQTT 3


// led gpio config in menuconfig
#define BLINK_GPIO CONFIG_BLINK_GPIO

/*
 * init the system tools.
 */
void init_systools();

/*
 * 打开led指示灯，可以通过云端控制
 */
void open_blink();

/**
 * 关闭led指示针，可以通过云端控制
 */
void close_blink();

/**
 * switch led for,if 0,switch for all led
 */
void switch_led(int led_code,int value);

// blink end

// nvs begin

void init_nvs();
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
// nvs end

// counter begin
/**
 * reboot_increase 1
 */
void reboot_increase(void);

/**
 * get restart count;
 */
int32_t get_count();
// counter end

// print heap begin
/**
 * open task print heap;
 */
void open_print_heap();

/**
 * close task print heap;
 */
void close_print_heap();
// print heap end