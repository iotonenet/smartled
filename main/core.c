#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"

#include "cJSON.h"
#include "mqtt_client.h"
#include "core.h"

#include "data/device_info.data"

void properties_set(cJSON *params)
{
    LOG_INFO("params:%s.",cJSON_Print(params));
}

void mqtt_msg_handler(esp_mqtt_event_handle_t event)
{
    LOG_INFO("topic len:%d.",event->topic_len);
    LOG_INFO("data len:%d.",event->data_len);
    char *topic = (char *)malloc(event->topic_len);
    char *data = (char *)malloc(event->data_len);
    memcpy(topic,event->topic,event->topic_len);
    topic[event->topic_len] = '\0';
    memcpy(data,event->data,event->data_len);
    data[event->data_len] = '\0';
    LOG_INFO("TOPIC=%s.", topic);
    LOG_INFO("DATA=%s.", data);
    if(strcmp(TOPIC_PROPERTY_SET, topic) == 0){
        LOG_INFO("property set msg recieved.");
        cJSON *dataJson = cJSON_Parse(data);
        cJSON *params = cJSON_GetObjectItem(dataJson,"params");
        properties_set(params);
    } else {
        LOG_INFO("other command recieved,%s.",topic);
    }
    LOG_INFO("[APP] Free memory: %d bytes", esp_get_free_heap_size());
}
