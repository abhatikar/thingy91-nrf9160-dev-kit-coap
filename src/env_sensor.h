#pragma once

#include <device.h>

// #define ENV_DEV DT_LABEL(DT_INST(0, bosch_bme680))
#define ENV_DEV "BME680"

typedef struct {
  float temperature;
  float humidity;
  float pressure;
  float gas_res;
} env_sensor_t;

const struct device *env_sensor_init();

void env_sensor_sample(env_sensor_t *env_sensor);
