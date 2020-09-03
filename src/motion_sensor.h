#pragma once

#include <device.h>

#define MOTION_DEV "ADXL362"

typedef struct {
	int32_t x;			/**< X-axis acceleration [m/s^2]. */
	int32_t y;			/**< y-axis acceleration [m/s^2]. */
	int32_t z;			/**< z-axis acceleration [m/s^2]. */
} motion_sensor_t;

struct device *motion_sensor_init();

void motion_sensor_sample(motion_sensor_t *motion_sensor);
