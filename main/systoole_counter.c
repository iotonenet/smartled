/*
 * counter.c
 *
 *  Created on: Sep 30, 2018
 *      Author: songfei
 */
#include <stdio.h>

#include "systools.h"

#define RESTART_COUNTER "reboot_counter"

void reboot_increase(void)
{
	int32_t current = read_i32(RESTART_COUNTER);
	write_i32(RESTART_COUNTER,++current);
}

int32_t get_count()
{
	// write_i32(RESTART_COUNTER,0);
	return read_i32(RESTART_COUNTER);
}
