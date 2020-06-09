#include <stdlib.h>

int rand_int(int min, int max) {
  return rand() % (max - min + 1) + min;
}

float rand_float(float min, float max) {
  return (max - min) * ((((float) rand()) / (float) RAND_MAX)) + min;
}
