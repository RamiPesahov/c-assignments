#include <stdio.h>

#define BITS_IN_BYTE 8 // one byte contains 8 bits
#define VALUE_OPTIONS_IN_BYTE 256 // 8 bits so it can have 2^8 different values

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
  
  int c;
  unsigned long int num_of_bytes = 0;
  unsigned long int one_occurences = 0;
  unsigned long int zero_occurences = 0;

  unsigned long int byte_occurences[VALUE_OPTIONS_IN_BYTE] = {0};
  

  // TODO: compute the statistics

  if(file == NULL) return stats; // check what to do -- cause it feels off

  while((c = fgetc(file)) != EOF) {

    byte_occurences[c]++;
    num_of_bytes++;
    
    unsigned char byte = (unsigned char)c;
    for (int i = 0; i < BITS_IN_BYTE; i++) {
  
      if((byte >> i) & 1)
        one_occurences++;

      else
        zero_occurences++;  
    }
  }

  int max = 0;
  unsigned char max_freq_byte = 0;
  for (int i = 0; i < VALUE_OPTIONS_IN_BYTE; i++)
  {
    if(byte_occurences[i] > max) {
      max = byte_occurences[i];
      max_freq_byte = (unsigned char)i;
    }
  }
  

  stats.cnt_bytes = num_of_bytes;
  stats.cnt_1 = one_occurences;
  stats.cnt_0 = zero_occurences;
  stats.byte_freq = max_freq_byte;

  if(stats.cnt_bytes > 0) { // if the file is not empty
    
    fseek(file,num_of_bytes / 2,SEEK_SET);
    stats.byte_mdl = fgetc(file);
  }
  
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
  FILE *file;
  if((file = fopen(argv[1],"rb")) == NULL) {

    printf("Error opening file: %s\n",argv[1]);
    return 0;
  }

  stats = compute_stats(file);  
  // print the results
  print_stats(stats);

  fclose(file);
  return 0;
}
