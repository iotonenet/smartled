/*
 * wifi_status.h
 *
 *  Created on: Sep 15, 2018
 *      Author: songfei
 */

#ifndef MAIN_WIFI_STATUS_H_
#define MAIN_WIFI_STATUS_H_


/**
 * blink when wifi connected
 */
void wifi_connect(void);

/**
 * stop blink when wifi disconnect
 */
void wifi_disconnect(void);

/**
 * get current wifi staus;
 */
int get_wifi_status(void);



#endif /* MAIN_WIFI_STATUS_H_ */
