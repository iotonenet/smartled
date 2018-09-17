/*
 * ble_status.h
 *
 *  Created on: Sep 15, 2018
 *      Author: songfei
 */

#ifndef MAIN_BLE_STATUS_H_
#define MAIN_BLE_STATUS_H_

/**
 * ble connect switch status
 */
void ble_connect(void);

/**
 * ble connect switch status
 */
void ble_disconnect(void);

/**
 * get current ble status;
 */
int get_ble_status(void);

#endif /* MAIN_BLE_STATUS_H_ */
