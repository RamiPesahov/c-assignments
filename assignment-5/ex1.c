#include <stdio.h>

unsigned int largest_power_of_2(unsigned int n) {
  // TODO
}

int main() {

  unsigned int n, L = 0;

  // get unsigned number from the user
  printf("Please enter an unsigned integer n:\n");
  scanf("%u", &n);

  // perform calculation
  L = largest_power_of_2(n);

  // print the result to the user
  printf("The Largest Power of 2 Smaller or Equal to %u is: %u\n", n, L);

  return 0;
}
