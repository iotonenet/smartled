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

#include "esp_log.h"
#include "mqtt_client.h"

#include "data/device_info.data"

/* These are pre-defined topics to subscribe */
#define TOPIC_PROPERTY_SET            "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/service/property/set"

/* These are pre-defined topics to publish*/
#define TOPIC_PROPERTY_POST            "/sys/"PRODUCT_KEY"/"DEVICE_NAME"/thing/event/property/post"


static const char *TAG = "MQTTS";

extern const uint8_t aliyuncs_com_pem_start[] asm("_binary_aliyuncs_com_pem_start");
extern const uint8_t aliyuncs_com_pem_end[]   asm("_binary_aliyuncs_com_pem_end");

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            LOG_INFO(TAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client, TOPIC_PROPERTY_SET, 0);
            LOG_INFO(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            // msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
            // LOG_INFO(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            // msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            // LOG_INFO(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            LOG_INFO(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            LOG_INFO(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, TOPIC_PROPERTY_POST, "data", 0, 0, 0);
            LOG_INFO(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            LOG_INFO(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            LOG_INFO(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            LOG_INFO(TAG, "MQTT_EVENT_DATA");
            LOG_INFO("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            LOG_INFO("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            LOG_INFO(TAG, "MQTT_EVENT_ERROR");
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

    LOG_INFO(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}

void init_mqtt()
{
    LOG_INFO(TAG, "[APP] mqtt startup..");

    esp_log_level_set("*", ESP_LOG_DEBUG);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_DEBUG);
    esp_log_level_set("TRANSPORT_TCP", ESP_LOG_DEBUG);
    esp_log_level_set("TRANSPORT_SSL", ESP_LOG_DEBUG);
    esp_log_level_set("TRANSPORT", ESP_LOG_DEBUG);
    esp_log_level_set("OUTBOX", ESP_LOG_DEBUG);

    mqtt_app_start();
}
