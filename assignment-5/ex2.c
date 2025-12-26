#include <stdbool.h>
#include <stdio.h>

bool is_binary_palindrome(unsigned int n) {
  // TODO
}

int main() {

  unsigned int n;
  bool result;

  // get unsigned number from the user
  printf("Please enter an unsigned integer n:\n");
  scanf("%u", &n);

  // check condition
  result = is_binary_palindrome(n);

  // print the result to the user
  printf("The binary representation of %u is %s\n", n,
         result ? "a palindrome" : "not a palindrome");

  return 0;
}
