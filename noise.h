#ifndef NOISE_H_
#define NOISE_H_

#include <stdint.h>

struct generator {
  void (*init)(void*);
  uint32_t (*next_sample)(void);
};

#endif
