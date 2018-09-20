/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#ifndef __SNIFFER_H__
#define __SNIFFER_H__
#include "esp_wifi.h"

typedef struct {
    uint8_t header[4];
    uint8_t dest_mac[6];
    uint8_t source_mac[6];
    uint8_t bssid[6];
    uint8_t payload[0];
} sniffer_payload_t;

typedef struct station_info {
    uint8_t  bssid[6];
    int8_t   rssi;
    uint8_t  channel;
    uint32_t timestamp;
    struct   station_info *next;
} station_info_t;

void wifi_sniffer_cb(void *recv_buf, wifi_promiscuous_pkt_type_t type);

/**
 * init sniffer task
 */
void init_sniffer(void);

#endif
