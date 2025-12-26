// TODO: add your includes here

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

  // TODO: check number of arguments

  // TODO: parse the arguments
}
