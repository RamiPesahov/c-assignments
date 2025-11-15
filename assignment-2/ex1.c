#include <stdio.h>

unsigned int even_digits(unsigned int number) {

    if(number == 0) return 0;

    unsigned int is_even = 0; // 1 if the digit is even and 0 otherwise

    if(number % 2 == 0 && number % 10 != 0) is_even++;

    return even_digits(number / 10) + is_even;
}

int main() {
    unsigned int num;
    unsigned int result;

    // Prompt user for input
    printf("Please insert a non-negative integer:\n");
    scanf("%u", &num);

    result = even_digits(num);

    // Prompt result to user
    printf("The number of even digits in %u is: %u\n", num, result);
    return 0;
}


