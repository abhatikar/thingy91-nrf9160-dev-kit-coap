#pragma once

#include "env_sensor.h"
#include "light_sensor.h"

typedef struct {
  env_sensor_t env_sensor;
  light_sensor_t light_sensor;
  s64_t uptime;
} MESSAGE;

void board_init(void);

void board_dump_message(u8_t *buffer, int len);