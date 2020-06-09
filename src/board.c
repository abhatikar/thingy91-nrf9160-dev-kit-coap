#include <stdio.h>

#include <zephyr.h>
#include <logging/log.h>

#include "board.h"
#include "env_sensor.h"
#include "light_sensor.h"

#define LOG_LEVEL CONFIG_BOARD_LOG_LEVEL
LOG_MODULE_REGISTER(BOARD);

MESSAGE last_message;

void board_init () {
  LOG_INF("Initialising board");

  if (NULL == env_sensor_init()) {
    LOG_INF("Unable to initialize environment sensor, falling back to simulated sensor.");
  }

  if (NULL == light_sensor_init()) {
    LOG_INF("Unable to initialize light sensor, falling back to simulated sensor.");
  }

}

void board_dump_message(u8_t *buffer, int len) {

  env_sensor_sample(&last_message.env_sensor);
  light_sensor_sample(&last_message.light_sensor);
  last_message.uptime = k_uptime_get() / 1000;

  snprintf(buffer, len, "%lld,%.2f,%.2f,%.2f,%.2f,%d,%d,%d,%d",
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
