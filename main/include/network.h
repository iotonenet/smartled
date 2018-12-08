#pragma once
#include "common.h"
#include "cJSON.h"

/**
 * init network component
 */
void init_network();

/**
 * init smart config
 */
void init_smart_config();

/**
 * init mqtt task
 */
void init_mqtt();

/**
 * post properties to mqtt
 */
void mqtt_propery_post(cJSON *params);