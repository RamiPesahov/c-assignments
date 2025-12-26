// TODO: add includes here

// encoding the packet fields according to the layout
static unsigned int encode_packet_header(header_t hdr) {
  // TODO
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

  // TODO: parse arguments

  // TODO: encode the packet header

  // TODO: print the encoded header
}
