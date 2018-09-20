/*
 * onenet_status.h
 *
 *  Created on: Sep 20, 2018
 *      Author: songfei
 */

#ifndef MAIN_INCLUDE_ONENET_STATUS_H_
#define MAIN_INCLUDE_ONENET_STATUS_H_

/**
 * blink when wifi connected
 */
void onenet_connect(void);

/**
 * stop blink when wifi disconnect
 */
void onenet_disconnect(void);

/**
 * get current wifi staus;
 */
int get_onenet_status(void);

#endif /* MAIN_INCLUDE_ONENET_STATUS_H_ */
