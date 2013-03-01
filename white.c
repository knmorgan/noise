#include "white.h"

#include <stdlib.h>
#include <time.h>

static uint16_t sample_size = 0;

void white_init(void* v) {
  uint16_t* arg = v;
  sample_size = *arg;
  srand(time(0));
}

uint32_t next_white_sample(void) {
  return rand() % (1 << sample_size);
}
