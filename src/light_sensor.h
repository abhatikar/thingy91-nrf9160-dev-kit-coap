#pragma once

#include <device.h>

// #define ENV_DEV DT_LABEL(DT_INST(0, bosch_bme680))
#define LIGHT_DEV "BH1749"

typedef struct {
  s32_t red;
  s32_t green;
  s32_t blue;
  s32_t ir;
} light_sensor_t;

struct device *light_sensor_init();

void light_sensor_sample(light_sensor_t *light_sensor);
