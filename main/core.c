#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"

#include "cJSON.h"
#include "mqtt_client.h"
#include "core.h"
#include "systools.h"
#include "constants.h"
#include "network.h"

#include "data/device_info.data"

void properties_set(cJSON *params)
{
    if(params == NULL){
        LOG_ERROR("property set params is empty.");
        return;
    }
    LOG_INFO("property set,params:%s.",cJSON_PrintUnformatted(params));
    // ScreenSwitch property set
    if(cJSON_HasObjectItem(params,"ScreenSwitch")){
        LOG_INFO("property set for ScreenSwitch.");
        int sw = cJSON_GetObjectItem(params,"ScreenSwitch")->valueint;
        if(sw){
            open_blink();
        } else {
            close_blink();
        }
    }
    mqtt_propery_post(params);
}

void properties_get(cJSON *params)
{
    if(params == NULL){
        LOG_ERROR("property get params is empty.");
        return;
    }
    LOG_INFO("property get,params:%s.",cJSON_PrintUnformatted(params));
}

void mqtt_msg_handler(esp_mqtt_event_handle_t event)
{
    LOG_INFO("topic:%.*s.",event->topic_len,event->topic);
    LOG_INFO("data:%.*s.",event->data_len,event->data);
    char *topic = (char *)malloc(event->topic_len);
    memcpy(topic,event->topic,event->topic_len);
    topic[event->topic_len] = '\0';
    
    cJSON *dataJson = cJSON_Parse(event->data);
    if(dataJson == NULL){
        LOG_ERROR("invalid data,%.*s.",event->data_len,event->data);
    }
    if(strcmp(TOPIC_PROPERTY_SET, topic) == 0){
        LOG_INFO("property set msg recieved.");
        properties_set(dataJson);
    } else if(strcmp(TOPIC_PROPERTY_GET, topic) == 0){
        LOG_INFO("property get msg recieved.");
        properties_set(dataJson);
    } else {
        LOG_INFO("other command recieved,%s.",topic);
    }
    // free(dataJson);
    dataJson = NULL;
    free(topic);
    topic = NULL;
    LOG_INFO("[APP] Free memory: %d bytes", esp_get_free_heap_size());
}
