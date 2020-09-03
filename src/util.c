#include <stdlib.h>

#define RAND_MAX 32767

// 7 -> rand()

int rand_int(int min, int max) {
  return 7 % (max - min + 1) + min;
}

float rand_float(float min, float max) {
  return (max - min) * ((((float) 7) / (float) RAND_MAX)) + min;
}
