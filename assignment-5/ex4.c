// TODO: add includes here
#include "parser.h"
#include <stdio.h>
#include <string.h>

// encoding the packet fields according to the layout
static unsigned int encode_packet_header(header_t hdr) {
  // TODO

  unsigned int packet = 0;
  packet |= (unsigned int)(hdr.version & 0x7) << 29;
  packet |= (unsigned int)(hdr.length & 0xF) << 25;
  packet |= (unsigned int)(hdr.type & 0x1F) << 20;
  packet |= (unsigned int)(hdr.src_node & 0x7F) << 13;
  packet |= (unsigned int)(hdr.dst_node & 0x7F) << 6;
  packet |= (unsigned int)(hdr.priority & 0x3) << 4;
  packet |= (unsigned int)(hdr.encrypted & 0x1) << 3;

  unsigned int checksum_code = 0;
  unsigned int temp = packet;

  while(temp != 0) {
    checksum_code += (temp & 1);
    temp >>= 1;
  }
  packet |= (checksum_code & 0x07); // modulu 8
  
  return packet;
}

// print header
static void print_header(unsigned int hdr_buf) {
  printf("The Encoded Packet Header is: 0x%08X\n", hdr_buf);
}

// the main function
// TODO: fill the code
int main(int argc, const char *argv[]) {
  header_t hdr = {};
  unsigned int hdr_buf;
  err_t ret;

  // TODO: check if need to print help (no args or only help)
  if(argc == 1 || (argc == 2 && strcmp(argv[1],HELP_FLAG) == 0)) { // no arguments, only the name of file or help flag
    
    print_help();
    return OK;
  } 

  // TODO: parse arguments
  ret = parse_args(argc, argv, &hdr);
  if(ret != OK) return ret;

  // TODO: encode the packet header
  hdr_buf = encode_packet_header(hdr);

  // TODO: print the encoded header
  print_header(hdr_buf);
}
