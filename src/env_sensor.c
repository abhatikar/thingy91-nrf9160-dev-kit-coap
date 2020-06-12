#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <logging/log.h>

#include "env_sensor.h"
#include "util.h"

#define LOG_LEVEL CONFIG_ENV_SENSOR_LOG_LEVEL
LOG_MODULE_REGISTER(ENV_SENSOR);

static struct device *env_dev = NULL;

struct device *env_sensor_init() {

  if (!env_dev) {

    if (IS_ENABLED(CONFIG_BME680)) {
      env_dev = device_get_binding(ENV_DEV);

      if (!env_dev) {
        LOG_WRN("Device driver not found");
        return NULL;
      }

      return env_dev;
    }
  }

  return NULL;
}

void env_sensor_sample(env_sensor_t *env_sensor) {
  int err;

  // Null out
  env_sensor->temperature = 0.0;
  env_sensor->humidity    = 0.0;
  env_sensor->pressure    = 0.0;
  env_sensor->gas_res     = 0.0;

  // Simulate
  if (env_dev == NULL) {
    env_sensor->temperature = rand_float(20.0, 29.0);
    env_sensor->humidity    = rand_float(40, 45);
    env_sensor->pressure    = rand_float(98, 99);
    env_sensor->gas_res     = rand_float(21980, 22000);

  } else {
    struct sensor_value temperature, pressure, humidity, gas_res;

    err = sensor_sample_fetch(env_dev);
    if (err == 0) {
      sensor_channel_get(env_dev, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
      sensor_channel_get(env_dev, SENSOR_CHAN_PRESS, &pressure);
      sensor_channel_get(env_dev, SENSOR_CHAN_HUMIDITY, &humidity);
      sensor_channel_get(env_dev, SENSOR_CHAN_GAS_RES, &gas_res);

      env_sensor->temperature = sensor_value_to_double(&temperature);
      env_sensor->humidity    = sensor_value_to_double(&humidity);
      env_sensor->pressure    = sensor_value_to_double(&pressure);
      env_sensor->gas_res     = sensor_value_to_double(&gas_res);
    }
  }
}
