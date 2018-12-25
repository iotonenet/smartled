#ifndef _Adafruit_NeoPixel_H
#define _Adafruit_NeoPixel_H

#include "common.h"
#include <stdint.h>
// #include "user_interface.h"
#include "rom/ets_sys.h"
#include "driver/gpio.h"

//thanks for https://github.com/cnlohr/ws2812esp8266 
//thanks for https://github.com/adafruit/Adafruit_NeoPixel

#define WSGPIO 13 //must use the ESP8266 GPIO0 as the pin to drive WS2812B RGB LED!!!
//user can change
#define PIXEL_MAX 8 //the total numbers of LEDs you are used in your project

//You will have to 	os_intr_lock();  	os_intr_unlock();

void setAllPixelColor(uint8_t r, uint8_t g, uint8_t b);
void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
void SetPixelColor(uint16_t n, uint32_t c);
uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
uint32_t Wheel(uint8_t WheelPos);
void rainbowCycle(uint8_t wait) ;
void theaterChase(uint32_t c, uint8_t wait);
void theaterChaseRainbow(uint8_t wait);
void colorWipe(uint32_t c, uint8_t wait);
void WS2812B_Test(void);
void WS2812B_Init(void);

#endif

