/*
 * onenet_status.c
 *
 *  Created on: Sep 20, 2018
 *      Author: songfei
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "onenet_status.h"

static int onenet_status = 0;

void onenet_connect(void)
{
	if(onenet_status == 0){
		onenet_status += 4;
	}
}

void onenet_disconnect(void)
{
	if(onenet_status > 0){
		onenet_status -= 4;
	}
}

int get_onenet_status(void)
{
	return onenet_status;
}


