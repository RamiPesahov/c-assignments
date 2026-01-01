// TODO: add your includes here

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

#define FIELDS_LEN(flags) (sizeof(flags) / sizeof(flags_t))

#define FIELDS_MIN 0
#define VERSION_MAX 7
#define LENGTH_MAX 15
#define PACKET_TYPE_MAX 31
#define NODE_MAX 127
#define PRIORITY_MAX 2
#define ENCRYPTED 1

typedef struct {
  const char *short_name;
  const char *long_name;
  const char *description;
  unsigned int min;
  unsigned int max;
} flags_t;

static const flags_t flags[] = {
    {HELP_FLAG, "Help", "Print this description", FIELDS_MIN, FIELDS_MIN},
    {"-v", "Version", "Protocol version", FIELDS_MIN, VERSION_MAX},
    {"-l", "Packet Length", "Packet length in 4 bytes units", FIELDS_MIN,
     LENGTH_MAX},
    {"-t", "Packet Type", "Packet type", FIELDS_MIN, PACKET_TYPE_MAX},
    {"-s", "Source Node", "Sender address", FIELDS_MIN, NODE_MAX},
    {"-d", "Destination Node", "Receiver address", FIELDS_MIN, NODE_MAX},
    {"-p", "Priority", "Priority class (0 = low … 2 = high)", FIELDS_MIN,
     PRIORITY_MAX},
    {"-e", "Encrypted", "1 if the packet is encrypted", FIELDS_MIN, ENCRYPTED}};

void print_help() {
  printf("Usage:\n");
  for (int i = 0; i < FIELDS_LEN(flags); i++) {
    printf("%*s%*s [%u-%u]:\t%s,\n", 4, flags[i].short_name, 17,
           flags[i].long_name, flags[i].min, flags[i].max,
           flags[i].description);
  }
  printf("Please try again.\n");
}

// parse the arguments, and fill p_hdr
err_t parse_args(int argc, const char *argv[], header_t *p_hdr) {

  // TODO: check parameters

  if(p_hdr == NULL || argv == NULL) {
    
    return ERR_PARAMS;
  }
  
  // TODO: check number of arguments
  
  if(argc == 1 || (argc == 2 && strcmp(argv[1],HELP_FLAG) == 0)) { // no arguments, only the name of file
    
    print_help();
    return OK;
  } 
  
  // 1 is the name of the file, 7 arguments and 7 for the values of each arguments 
  if(argc != 15) {

    printf("Error: number of given arguements %d is different than expected",argc);
    return ERR_NUM_ARGS;
  }
  
  // TODO: parse the arguments

  unsigned int packet = 0;

  for (int i = 1; i < argc; i += 2) { // argv[0] is the file name, i+= 2 beacuse one argument is the flag and the next one is their value

    int flag = -1; // initlized to no flag yet
    for (int j = 1; j < FIELDS_LEN(flags); j++) { // skip the first flag which is the help beacause we already handled this case
      
      if(strcmp(argv[i],flags[j].short_name) == 0) {

        flag = j;
        break;
      }
    }

    if (flag == -1) {
      printf("Error: Unknown flag: \"%s\"",argv[i]);
      return ERR_UNKNOWN_FLAG;
    }
    
    if(i + 1 >= argc || argv[i + 1][0] == '-') {

      printf("Error: Missing argument for flag \"%s\"",argv[i + 1]);
      return ERR_MISSING_ARG;
    }
    
    int value_of_flag = atoi(argv[i+1]);

    if(value_of_flag < (int)flags[flag].min || value_of_flag > (int)flags[flag].max) {

      printf("Error: value %d for flag \"%s\" (%s) is out of range [%u-%u]",value_of_flag,flags[flag].short_name,flags[flag].long_name,flags[flag].min,flags[flag].max);
      return ERR_INVALID_VALUE;
    }

    switch(flag) {

      case 1:
        p_hdr -> version = (unsigned char)value_of_flag;
        packet |= (unsigned int)(value_of_flag & 0x7) << 29;
        break;

      case 2:
        p_hdr -> length = (unsigned char)value_of_flag;
        packet |= (unsigned int)(value_of_flag & 0xF) << 25;
        break;
      
      case 3:
        p_hdr -> type = (unsigned char)value_of_flag;
        packet |= (unsigned int)(value_of_flag & 0x1F) << 20;
        break;
      
      case 4:
        p_hdr -> src_node = (unsigned char)value_of_flag;
        packet |= (unsigned int)(value_of_flag & 0x7F) << 13;
        break;
      
      case 5:
        p_hdr -> dst_node = (unsigned char)value_of_flag;
        packet |= (unsigned int)(value_of_flag & 0x7F) << 6;
        break;
        
      case 6:
        p_hdr -> priority = (unsigned char)value_of_flag;
        packet |= (unsigned int)(value_of_flag & 0x3) << 4;
        break;
          
      case 7:
        p_hdr -> encrypted = (value_of_flag == 1);
        packet |= (unsigned int)(value_of_flag & 0x1) << 3;
        break;

      default:
        break;  
    }
    
    
  }
  
  unsigned int checksum_code = 0;
  unsigned int temp = packet;
  while(temp != 0) {
    checksum_code += (temp & 1);
    temp >>= 1;
  }
  
  packet |= (checksum_code & 0x07); // modulu 8
  printf("The Encoded Packet Header is: %X",packet);
  return OK;
}
