/*
 * wifi_status.c
 *
 *  Created on: Sep 15, 2018
 *      Author: songfei
 */
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "wifi_status.h"

static int wifi_status = 0;

void wifi_connect(void)
{
	if(wifi_status == 0){
		wifi_status += 2;
	}
}

void wifi_disconnect(void)
{
	if(wifi_status > 0){
		wifi_status -= 2;
	}
}

int get_wifi_status(void)
{
	return wifi_status;
}
