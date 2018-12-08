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

#include "data/device_info.data"

void properties_set(cJSON *params)
{
    if(params == NULL){
        LOG_ERROR("property set params is empty.");
        return;
    }
    LOG_INFO("params:%s.",cJSON_Print(params));
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

}

void mqtt_msg_handler(esp_mqtt_event_handle_t event)
{
    LOG_INFO("topic:%.*s.",event->topic_len,event->topic);
    LOG_INFO("data:%.*s.",event->data_len,event->data);
    // LOG_INFO("data len:%d.",event->data_len);
    // char *topic = (char *)malloc(event->topic_len);
    // char *data = (char *)malloc(event->data_len);
    // memcpy(topic,event->topic,event->topic_len);
    // topic[event->topic_len] = '\0';
    // memcpy(data,event->data,event->data_len);
    // data[event->data_len] = '\0';
    cJSON *dataJson = cJSON_Parse(event->data);
    if(dataJson == NULL){
        LOG_ERROR("invalid data,%.*s.",event->data_len,event->data);
    }
    char *method = cJSON_GetObjectItem(dataJson,"method")->valuestring;
    // LOG_INFO("TOPIC=%s.", topic);
    // LOG_INFO("DATA=%s.", data);
    if(strcmp(METHOD_PROPERTY_SET, method) == 0){
        LOG_INFO("property set msg recieved.");
        properties_set(cJSON_GetObjectItem(dataJson,"params"));
    } else {
        LOG_INFO("other command recieved,%s.",method);
    }
    cJSON_Delete(dataJson);
    free(method);
    LOG_INFO("[APP] Free memory: %d bytes", esp_get_free_heap_size());

}
