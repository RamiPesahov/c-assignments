#include <stdbool.h>
#include <stdio.h>

unsigned int reverse(unsigned int n) {

  unsigned int reversed = 0;
  
  while(n != 0) {

    reversed <<= 1;
    reversed |= (n & 1); // copy only the LSB of n
    n >>= 1; 
  }

  return reversed;
}

bool is_binary_palindrome(unsigned int n) {
  // TODO

  if (n == 0) return true;

  unsigned int reversed = reverse(n);

  if(n == reversed)
    return true;

  else 
    return false;  
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
