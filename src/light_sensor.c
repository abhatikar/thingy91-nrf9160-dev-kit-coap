#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <logging/log.h>

#include "light_sensor.h"
#include "util.h"

#define LOG_LEVEL CONFIG_LIGHT_SENSOR_LOG_LEVEL
LOG_MODULE_REGISTER(LIGHT_SENSOR);

static const struct device *light_dev = NULL;

const struct device *light_sensor_init() {

  if (!light_dev) {

    if (IS_ENABLED(CONFIG_BH1749)) {
      light_dev = device_get_binding(LIGHT_DEV);

      if (!light_dev) {
        LOG_WRN("Device driver not found");
        return NULL;
      }

      return light_dev;
    }
  }

  return NULL;
}

void light_sensor_sample(light_sensor_t *light_sensor) {
  int err;

  // Null out
  light_sensor->red   = 0;
  light_sensor->green = 0;
  light_sensor->blue  = 0;
  light_sensor->ir    = 0;

  // Simulate
  if (light_dev == NULL) {
    light_sensor->red   = rand_int(500, 1000);
    light_sensor->green = rand_int(500, 1000);
    light_sensor->blue  = rand_int(500, 1000);
    light_sensor->ir    = rand_int(500, 1000);

  } else {
    struct sensor_value red, green, blue, ir;

    err = sensor_sample_fetch(light_dev);
    if (err == 0) {
      sensor_channel_get(light_dev, SENSOR_CHAN_RED, &red);
      sensor_channel_get(light_dev, SENSOR_CHAN_GREEN, &green);
      sensor_channel_get(light_dev, SENSOR_CHAN_BLUE, &blue);
      sensor_channel_get(light_dev, SENSOR_CHAN_IR, &ir);

      light_sensor->red   = sensor_value_to_double(&red);
      light_sensor->green = sensor_value_to_double(&green);
      light_sensor->blue  = sensor_value_to_double(&blue);
      light_sensor->ir    = sensor_value_to_double(&ir);
    }
  }
}
