/*
 * smartled.h
 *
 *  Created on: Sep 11, 2018
 *      Author: songfei
 */
#pragma once
#include "common.h"
#include "mqtt_client.h"

/**
 * mqtt message handler.
 */
void mqtt_msg_handler(esp_mqtt_event_handle_t event);
