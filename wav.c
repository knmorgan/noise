#include "wav.h"

static inline uint32_t get_file_size(struct fmt_chunk* fmt, uint32_t samples) {
  return 36 + (samples * fmt->num_channels * fmt->bits_per_sample / 8);
}

static inline void write_wav_header(FILE* f, uint32_t file_size) {
  fwrite("RIFF", sizeof(char), 4, f);
  fwrite(&file_size, sizeof(file_size), 1, f);
  fwrite("WAVE", sizeof(char), 4, f);
}

static inline void write_fmt_chunk(FILE* f, struct fmt_chunk* fmt) {
  const char* fmt_id = "fmt ";
  uint32_t size = 16; /* Will always be 16 bytes for PCM data. */

  fwrite(fmt_id, sizeof(char), 4, f);
  fwrite(&size, sizeof(size), 1, f);
  fwrite(&fmt->audio_format, sizeof(fmt->audio_format), 1, f);
  fwrite(&fmt->num_channels, sizeof(fmt->num_channels), 1, f);
  fwrite(&fmt->sample_rate, sizeof(fmt->sample_rate), 1, f);
  fwrite(&fmt->byte_rate, sizeof(fmt->byte_rate), 1, f);
  fwrite(&fmt->block_align, sizeof(fmt->block_align), 1, f);
  fwrite(&fmt->bits_per_sample, sizeof(fmt->bits_per_sample), 1, f);
}

static inline void write_data_chunk(FILE* f, struct fmt_chunk* fmt, struct generator* gen, uint32_t samples) {
  //TODO: do this
  const char* data_id = "data";
  uint32_t size = samples * fmt->num_channels * fmt->bits_per_sample / 8;

  fwrite(data_id, sizeof(char), 4, f);
  fwrite(&size, sizeof(size), 1, f);
  
  int i, bytes_per_sample = fmt->bits_per_sample / 8;
  for(i = 0; i < samples; ++i) {
    uint32_t sample = gen->next_sample();
    fwrite(&sample, bytes_per_sample, 1, f);
  }
}

void generate_wav(FILE* f, struct fmt_chunk* fmt, struct generator* gen, uint32_t samples) {
  write_wav_header(f, get_file_size(fmt, samples));
  write_fmt_chunk(f, fmt);
  write_data_chunk(f, fmt, gen, samples);
}
