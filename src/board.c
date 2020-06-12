#include <stdio.h>

#include <zephyr.h>
#include <logging/log.h>

#include "board.h"
#include "modem.h"
#include "env_sensor.h"
#include "light_sensor.h"
#include "led.h"

#define LOG_LEVEL CONFIG_BOARD_LOG_LEVEL
LOG_MODULE_REGISTER(BOARD);

enum {
  MESSAGE_MODEM,
  MESSAGE_SENSORS,
};

static MESSAGE last_message;

void board_init () {
  LOG_INF("Initialising board");

  modem_init();

  if (NULL == env_sensor_init()) {
    LOG_INF("Unable to initialize environment sensor, falling back to simulated sensor.");
  }

  if (NULL == light_sensor_init()) {
    LOG_INF("Unable to initialize light sensor, falling back to simulated sensor.");
  }

  if (NULL == led_init()) {
    LOG_INF("Unable to initialize LED, darkness follows.");
  }

}

void board_dump_modem_message(u8_t *buffer, int len) {

  modem_sample(&last_message.modem);
  last_message.uptime = k_uptime_get() / 1000;

  snprintf(buffer, len, "%d,%lld,%d,%d,%d,%d,%d,%d,%d,%s",
    MESSAGE_MODEM,
    last_message.uptime,
    last_message.modem.current_band,
    last_message.modem.sup_band,
    last_message.modem.area_code,
    last_message.modem.current_operator,
    last_message.modem.mcc,
    last_message.modem.mnc,
    last_message.modem.cellid_hex,
    last_message.modem.ip_address);
}

void board_dump_message(u8_t *buffer, int len) {

  env_sensor_sample(&last_message.env_sensor);
  light_sensor_sample(&last_message.light_sensor);
  last_message.uptime = k_uptime_get() / 1000;

  snprintf(buffer, len, "%d,%lld,%.2f,%.2f,%.2f,%.2f,%d,%d,%d,%d",
    MESSAGE_SENSORS,
    last_message.uptime,
    last_message.env_sensor.temperature,
    last_message.env_sensor.humidity,
    last_message.env_sensor.pressure,
    last_message.env_sensor.gas_res,
    last_message.light_sensor.red,
    last_message.light_sensor.green,
    last_message.light_sensor.blue,
    last_message.light_sensor.ir);
}
