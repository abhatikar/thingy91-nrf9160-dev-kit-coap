#pragma once

#include <device.h>

// #define ENV_DEV DT_LABEL(DT_INST(0, bosch_bme680))
#define LIGHT_DEV "BH1749"

typedef struct {
  int32_t red;
  int32_t green;
  int32_t blue;
  int32_t ir;
} light_sensor_t;

const struct device *light_sensor_init();

void light_sensor_sample(light_sensor_t *light_sensor);
