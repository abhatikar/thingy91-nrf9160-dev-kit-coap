#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <logging/log.h>

#include "motion_sensor.h"
#include "util.h"

#define LOG_LEVEL CONFIG_MOTION_SENSOR_LOG_LEVEL
LOG_MODULE_REGISTER(MOTION_SENSOR);

static struct device *motion_dev = NULL;

struct device *motion_sensor_init() {

  if (!motion_dev) {

    if (IS_ENABLED(CONFIG_ADXL362)) {
      motion_dev = device_get_binding(MOTION_DEV);

      if (!motion_dev) {
        LOG_WRN("Device driver not found");
        return NULL;
      }

      return motion_dev;
    }
  }

  return NULL;
}

void motion_sensor_sample(motion_sensor_t *motion_sensor) {
  int err;

  // Null out
  motion_sensor->x = 0;
  motion_sensor->y = 0;
  motion_sensor->z = 0;

  // Simulate
  if (motion_dev == NULL) {
    motion_sensor->x = rand_int(0, 360);
    motion_sensor->y = rand_int(0, 360);
    motion_sensor->z = rand_int(0, 360);

  } else {
    struct sensor_value accel_data[3];

    err = sensor_sample_fetch_chan(motion_dev, SENSOR_CHAN_ALL);
    if (err == 0) {
      sensor_channel_get(motion_dev, SENSOR_CHAN_ACCEL_X, &accel_data[0]);
      sensor_channel_get(motion_dev, SENSOR_CHAN_ACCEL_Y, &accel_data[1]);
      sensor_channel_get(motion_dev, SENSOR_CHAN_ACCEL_Z, &accel_data[2]);

      motion_sensor->x = sensor_value_to_double(&accel_data[0]);
      motion_sensor->y = sensor_value_to_double(&accel_data[1]);
      motion_sensor->z = sensor_value_to_double(&accel_data[2]);
    }
  }
}
