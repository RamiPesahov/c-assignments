#include <stdio.h>

unsigned int sum_digits(unsigned int number) {

      unsigned int current_sum;

    if(number < 10) return number;

    current_sum = sum_digits(number / 10) + (number % 10);

    current_sum = sum_digits(current_sum);

    return current_sum;

}

int main() {
    unsigned int num;
    unsigned int result;

    // Prompt user for input
    printf("Please insert a non-negative integer:\n");
    scanf("%u", &num);

    result = sum_digits(num);

    // Prompt result to user
    printf("The repeated sum of digits in %u is: %u\n", num, result);
    return 0;
}

