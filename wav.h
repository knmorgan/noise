#ifndef WAV_H_
#define WAV_H_

#include "noise.h"

#include <stdint.h>
#include <stdio.h>

struct fmt_chunk {
  uint16_t audio_format;
  uint16_t num_channels;
  uint32_t sample_rate;
  uint32_t byte_rate;
  uint16_t block_align;
  uint16_t bits_per_sample;
};

void generate_wav(FILE*, struct fmt_chunk*, struct generator*, uint32_t);

#endif
