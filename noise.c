#include "noise.h"
#include "pink.h"
#include "wav.h"
#include "white.h"

int main(int argc, char** argv) {
  struct generator g;
  g.init = white_init;
  g.next_sample = next_white_sample;

  struct fmt_chunk fmt;
  fmt.audio_format = 1;
  fmt.num_channels = 1;
  fmt.sample_rate = 44100;
  fmt.byte_rate = 88200;
  fmt.block_align = 2;
  fmt.bits_per_sample = 16;

  uint16_t white_args = 16;

  g.init(&white_args);
  FILE* f = fopen("test.wav", "w");
  generate_wav(f, &fmt, &g, 100000);
  fclose(f);
}
