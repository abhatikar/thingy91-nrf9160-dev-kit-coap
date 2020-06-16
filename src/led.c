#include <zephyr.h>
#include <device.h>
#include <drivers/pwm.h>
#include <logging/log.h>

#include "led.h"

#define LOG_LEVEL CONFIG_LED_LOG_LEVEL
LOG_MODULE_REGISTER(LED);

static led_t led;
static const size_t led_pins[3] = {
  LED_RED_PIN,
  LED_GREEN_PIN,
  LED_BLUE_PIN,
};
static struct led_effect effects[] = {
  [LED_PATTERN_NORMAL] = LED_EFFECT_LED_BREATHE(500, 500, LED_COLOR_CYAN),
  [LED_PATTERN_SENDING] = LED_EFFECT_LED_BLINK(200, LED_COLOR_GREEN),
};

static void pwm_out(led_t *led, struct led_color *color) {
  for (size_t i = 0; i < ARRAY_SIZE(color->c); i++) {
    pwm_pin_set_usec(led->pwm_dev, led_pins[i],
      255, color->c[i], 0);
  }
}

static void pwm_off(led_t *led) {
  struct led_color nocolor = {0};

  pwm_out(led, &nocolor);
}

static void work_handler(struct k_work *work) {
  led_t *w_led = CONTAINER_OF(work, led_t, work);
  const struct led_effect_step *effect_step =
    &led.effect->steps[led.effect_step];
  int substeps_left = effect_step->substep_count - led.effect_substep;

  for (size_t i = 0; i < ARRAY_SIZE(led.color.c); i++) {
    int diff = (effect_step->color.c[i] - led.color.c[i]) /
      substeps_left;
    led.color.c[i] += diff;
  }

  pwm_out(w_led, &led.color);

  led.effect_substep++;
  if (led.effect_substep == effect_step->substep_count) {
    led.effect_substep = 0;
    led.effect_step++;

    if (led.effect_step == led.effect->step_count) {
      if (led.effect->loop_forever) {
        led.effect_step = 0;
      }
    } else {
      __ASSERT_NO_MSG(led.effect->steps[led.effect_step].substep_count > 0);
    }
  }

  if (led.effect_step < led.effect->step_count) {
    s32_t next_delay =
      led.effect->steps[led.effect_step].substep_time;

    k_delayed_work_submit(&led.work, K_MSEC(next_delay));
  }
}

static void led_update(led_t *c_led) {
  k_delayed_work_cancel(&c_led->work);

  c_led->effect_step = 0;
  c_led->effect_substep = 0;

  if (!c_led->effect) {
    LOG_DBG("No effect set");
    return;
  }

  __ASSERT_NO_MSG(c_led->effect->steps);

  if (c_led->effect->step_count > 0) {
    s32_t next_delay =
      c_led->effect->steps[c_led->effect_step].substep_time;

    k_delayed_work_submit(&c_led->work, K_MSEC(next_delay));
  } else {
    LOG_DBG("LED effect with no effect");
  }
}

struct device *led_init() {

  if (!led.pwm_dev) {

    led.pwm_dev = device_get_binding(LED_DEV);

    if (!led.pwm_dev) {
      LOG_WRN("Device driver not found");
      return NULL;
    }

    k_delayed_work_init(&led.work, work_handler);
    led_update(&led);

    return led.pwm_dev;
  }

  return NULL;

}

void led_set_effect(enum led_pattern pattern) {
  led.effect = &effects[pattern];
  led_update(&led);
}
