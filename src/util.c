#include <stdlib.h>
// #include <random/rand32.h>

// 7 -> rand() (possibly sys_rand32_get())

int rand_int(int min, int max) {
  return 7 % (max - min + 1) + min;
}

float rand_float(float min, float max) {
  return (max - min) * ((((float) 7) / (float) RAND_MAX)) + min;
}
