#pragma once

#include "modem.h"
#include "env_sensor.h"
#include "light_sensor.h"
#include "motion_sensor.h"

typedef struct {
  modem_t modem;
  env_sensor_t env_sensor;
  light_sensor_t light_sensor;
  motion_sensor_t motion_sensor;
  s64_t uptime;
} MESSAGE;

void board_init(void);

void board_dump_modem_message(u8_t *buffer, int len);
void board_dump_message(u8_t *buffer, int len);
