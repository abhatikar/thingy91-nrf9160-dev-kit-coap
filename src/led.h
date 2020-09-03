#pragma once

#include <device.h>

#define LED_DEV "PWM_0"

#define LED_RED_PIN   29
#define LED_GREEN_PIN 30
#define LED_BLUE_PIN  31

struct led_color {
  uint8_t c[3];
};

struct led_effect_step {
  struct led_color color;
  uint16_t substep_count;
  uint16_t substep_time;
};

struct led_effect {
  struct led_effect_step *steps;
  uint16_t step_count;
  bool loop_forever;
};

typedef struct {
  struct device *pwm_dev;

  size_t id;
  struct led_color color;
  const struct led_effect *effect;
  uint16_t effect_step;
  uint16_t effect_substep;

  struct k_delayed_work work;
} led_t;

#define LED_COLOR(_r, _g, _b) { \
  .c = {_r, _g, _b}             \
}
#define LED_NOCOLOR() {         \
  .c = {0, 0, 0}                \
}

#define LED_EFFECT_LED_ON(_color) {             \
  .steps = ((struct led_effect_step[]) {        \
    {                                           \
      .color = _color,                          \
      .substep_count = 1,                       \
      .substep_time = 0,                        \
    },                                          \
  }),                                           \
  .step_count = 1,                              \
  .loop_forever = false,                        \
}

#define LED_EFFECT_LED_BLINK(_period, _color) { \
  .steps = ((struct led_effect_step[]) {        \
    {                                           \
      .color = _color,                          \
      .substep_count = 1,                       \
      .substep_time = (_period),                \
    },                                          \
    {                                           \
      .color = LED_NOCOLOR(),                   \
      .substep_count = 1,                       \
      .substep_time = (_period),                \
    },                                          \
  }),                                           \
  .step_count = 2,                              \
  .loop_forever = true,                         \
}

#define _BREATH_SUBSTEPS 15
#define _BREATH_PAUSE_SUBSTEPS 1
#define LED_EFFECT_LED_BREATHE(_period, _pause, _color) { \
  .steps = ((struct led_effect_step[]) {                  \
    {                                                     \
      .color = _color,                                    \
      .substep_count = _BREATH_SUBSTEPS,                  \
      .substep_time = ((_period +                         \
        (_BREATH_SUBSTEPS - 1))                           \
        / _BREATH_SUBSTEPS),                              \
    },                                                    \
    {                                                     \
      .color = _color,                                    \
      .substep_count = 1,                                 \
      .substep_time = _period,                            \
    },                                                    \
    {                                                     \
      .color = LED_NOCOLOR(),                             \
      .substep_count = _BREATH_SUBSTEPS,                  \
      .substep_time = ((_period +                         \
        (_BREATH_SUBSTEPS - 1))                           \
        / _BREATH_SUBSTEPS),                              \
    },                                                    \
    {                                                     \
      .color = LED_NOCOLOR(),                             \
      .substep_count = _BREATH_PAUSE_SUBSTEPS,            \
      .substep_time = _pause,                             \
    },                                                    \
  }),                                                     \
  .step_count = 4,                                        \
  .loop_forever = true,                                   \
}

#define LED_EFFECT_LED_OFF() LED_EFFECT_LED_ON(LED_NOCOLOR())

#define LED_MAX           50
#define LED_COLOR_OFF     LED_COLOR(0, 0, 0)
#define LED_COLOR_RED     LED_COLOR(LED_MAX, 0, 0)
#define LED_COLOR_GREEN   LED_COLOR(0, LED_MAX, 0)
#define LED_COLOR_BLUE    LED_COLOR(0, 0, LED_MAX)
#define LED_COLOR_WHITE   LED_COLOR(LED_MAX, LED_MAX, LED_MAX)
#define LED_COLOR_YELLOW  LED_COLOR(LED_MAX, LED_MAX, 0)
#define LED_COLOR_CYAN    LED_COLOR(0, LED_MAX, LED_MAX)
#define LED_COLOR_PURPLE  LED_COLOR(LED_MAX, 0, LED_MAX)

enum led_pattern {
  LED_PATTERN_NORMAL,
  LED_PATTERN_SENDING,
};

struct device *led_init();

void led_set_effect(enum led_pattern pattern);
