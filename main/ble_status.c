/*
 * ble_status.c
 *
 *  Created on: Sep 15, 2018
 *      Author: songfei
 */
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "ble_status.h"

static int ble_status = 0;

void ble_connect(void)
{
	if(ble_status == 0){
		ble_status += 1;
	}
}

void ble_disconnect(void)
{
	if(ble_status > 0){
		ble_status -= 1;
	}
}

int get_ble_status(void)
{
	return ble_status;
}
