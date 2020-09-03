/**
 *  Copyright (c) 2020 Telenor Norway ASA
 *  Author: Pontus Aurdal <pontus.aurdal@telenor.com>
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <zephyr.h>
#include <stdio.h>
#include <net/coap.h>
#include <net/coap_utils.h>
#include <net/socket.h>
#include <logging/log.h>

#include "board.h"
#include "led.h"

#define LOG_LEVEL CONFIG_MAIN_LOG_LEVEL
LOG_MODULE_REGISTER(MAIN);

#define SEND_INTERVAL_MS 10000

static uint8_t coap_buffer[256];

static struct sockaddr_in remote_addr = {
  .sin_family = AF_INET,
  .sin_port = htons(CONFIG_COAP_SERVER_PORT)
};

int ccb(const struct coap_packet *response, struct coap_reply *reply, const struct sockaddr *from) {
  const uint8_t *payload;
  uint16_t payload_len;
	uint8_t temp_buf[16];

  payload = coap_packet_get_payload(response, &payload_len);

	snprintf(temp_buf, MAX(payload_len, sizeof(temp_buf)), "%s", payload);

  printk("CoAP response: code: 0x%x, payload: %s\n",
	       coap_header_get_code(response), temp_buf);

	return 0;
}

void main(void) {
  int64_t next_send_time = SEND_INTERVAL_MS;
  int err;

  board_init();
  coap_init(AF_INET);

  led_set_effect(LED_PATTERN_NORMAL);
  LOG_INF("Board inited! %s", CONFIG_BOARD);

  net_addr_pton(AF_INET, CONFIG_COAP_SERVER_IP, &remote_addr.sin_addr);

  next_send_time = k_uptime_get();

  while (1) {

    if (k_uptime_get() >= next_send_time) {

      led_set_effect(LED_PATTERN_SENDING);

      board_dump_modem_message(coap_buffer, sizeof(coap_buffer));
      LOG_INF("Uplink payload (modem): %s", log_strdup((char *)coap_buffer));
      err = coap_send_request(COAP_METHOD_POST, (struct sockaddr *)&remote_addr,
                              NULL, coap_buffer, strlen(coap_buffer), ccb);

      board_dump_message(coap_buffer, sizeof(coap_buffer));
      LOG_INF("Uplink payload (sensor): %s", log_strdup((char *)coap_buffer));
      err = coap_send_request(COAP_METHOD_POST, (struct sockaddr *)&remote_addr,
                              NULL, coap_buffer, strlen(coap_buffer), ccb);

      k_sleep(K_MSEC(500));
      led_set_effect(LED_PATTERN_NORMAL);

      // Todo: make CoAP GET request
      err = coap_send_request(COAP_METHOD_GET, (struct sockaddr *)&remote_addr,
                              NULL, NULL, NULL, &ccb);
      LOG_INF("GET request");

      next_send_time += SEND_INTERVAL_MS;
    }

    int64_t remaining = next_send_time - k_uptime_get();
    if (remaining < 0) {
      remaining = 0;
    }
    k_sleep(K_MSEC(remaining));
  }
}
