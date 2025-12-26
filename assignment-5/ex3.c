#include <stdio.h>

typedef struct {
  unsigned long int cnt_1;
  unsigned long int cnt_0;
  unsigned long int cnt_bytes;
  unsigned char byte_freq;
  unsigned char byte_mdl;
} stats_t;

static void print_stats(stats_t stats) {
  printf("Total bits set to 1: %lu\n", stats.cnt_1);
  printf("Total bits set to 0: %lu\n", stats.cnt_0);
  printf("Total number of bytes: %lu\n", stats.cnt_bytes);
  printf("Most frequent byte value: 0x%X\n", stats.byte_freq);
  printf("Middle byte value: 0x%X\n", stats.byte_mdl);
}

static stats_t compute_stats(FILE *file) {
  stats_t stats = {};

  // TODO: compute the statistics

  return stats;
}

int main(int argc, char *argv[]) {
  stats_t stats;

  // check input argument
  if (argc != 2) {
    printf("Usage: %s <binary_file>\n", argv[0]);
    return 0;
  }

  // TODO: compute stats from file

  // print the results
  print_stats(stats);

  return 0;
}
