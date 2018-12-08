#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "cJSON.h"
#include "mqtt_client.h"
#include "network.h"
#include "systools.h"
#include "core.h"
#include "constants.h"

#include "data/device_info.data"

extern const uint8_t aliyuncs_com_pem_start[] asm("_binary_aliyuncs_com_pem_start");
extern const uint8_t aliyuncs_com_pem_end[]   asm("_binary_aliyuncs_com_pem_end");

static esp_mqtt_client_handle_t mqtt_client = NULL;

void mqtt_propery_post(cJSON *params)
{
    if(mqtt_client == NULL){
        LOG_ERROR("mqtt_client is null.propery can not post.%s.",cJSON_Print(params));
        return;
    }
    LOG_INFO("properties to post:%s.",cJSON_PrintUnformatted(params));
    cJSON *data = cJSON_CreateObject();
    cJSON_AddStringToObject(data,"method",METHOD_PROPERTY_POST);
    cJSON_AddItemToObject(data,"params",params);
    esp_mqtt_client_publish(mqtt_client, TOPIC_PROPERTY_POST, cJSON_PrintUnformatted(data), 0, 0, 0);
    cJSON_Delete(data);
    LOG_INFO("properties post successful.");
}

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            LOG_INFO("MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client, TOPIC_PROPERTY_SET, 0);
            LOG_INFO("sent subscribe successful, msg_id=%d", msg_id);

            // msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
            // ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            // msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            // ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
            switch_led(CODE_LED_MQTT,1);
            break;
        case MQTT_EVENT_DISCONNECTED:
            LOG_INFO("MQTT_EVENT_DISCONNECTED");
            switch_led(CODE_LED_MQTT,0);
            break;

        case MQTT_EVENT_SUBSCRIBED:
            LOG_INFO("MQTT_EVENT_SUBSCRIBED, msg_id=%d.", event->msg_id);
            // post reboot counter.
            cJSON *params = cJSON_CreateObject();
            cJSON_AddNumberToObject(params,"RebootCounter",get_count());
            mqtt_propery_post(params);
            // free(params);
            params = NULL;
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            LOG_INFO("MQTT_EVENT_UNSUBSCRIBED, msg_id=%d.", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            LOG_INFO("MQTT_EVENT_PUBLISHED, msg_id=%d.", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            LOG_INFO("MQTT_EVENT_DATA");
            mqtt_msg_handler(event);
            // printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            // printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            LOG_INFO("MQTT_EVENT_ERROR");
            break;
    }
    return ESP_OK;
}

static void mqtt_app_start(void)
{
    const esp_mqtt_client_config_t mqtt_cfg = {
        .uri = MQTT_URI,
        .event_handle = mqtt_event_handler,
        .client_id = MQTT_CLIENT_ID,
        .username = MQTT_USERNAME,
        .password = MQTT_PASSWORD,
        .cert_pem = (const char *)aliyuncs_com_pem_start,
    };

    LOG_INFO("[APP] Free memory: %d bytes", esp_get_free_heap_size());
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(mqtt_client);
}

void init_mqtt()
{
    LOG_INFO("[APP] mqtt startup..");

    mqtt_app_start();
}
