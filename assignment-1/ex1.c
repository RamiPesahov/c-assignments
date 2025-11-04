#include <stdio.h>

int main() {

    int number, base, num_digits, sum_digits = 0, temp, abs_value;
    char sign;

    printf("Please enter a number (integer) and a base:\n");
    scanf("%d %d",&number,&base);

    while(base != 8 && base != 10 && base != 16) {

        printf("Invalid base %d\n",base);
        printf("Please enter a valid base [8,10,16]:\n");
        scanf("%d",&base);
    }

    printf("Here is some information about the given numbers: %d\n",number);

    if(number > 0)
    sign = '+';
    
    else if (number == 0)
    sign = '0';

    else 
    sign = '-';

    printf("Its sign is: %c",sign);

    temp = number;

    if(sign == '-')
    abs_value = -temp;

    else 
    abs_value = temp;

    printf("Decimal representation of the absolute value: %d\n",abs_value);

    if(temp == 0) 
        num_digits = 1;
    
    while(temp != 0) {

        num_digits++;
        sum_digits += temp % 10;
        temp /= 10;
    }

    printf("The number of digits is: $d\n",num_digits);
    printf("The sum of digits is: %d\n",sum_digits);

    switch(base) {

    case 8:
        printf("0d%d = %o\n",abs_value,abs_value);
        break;

    case 16:
        printf("0d%d = %#x\n",abs_value,abs_value);
        break;

    case 10:
        printf("Base 10 representation was already computed above.\n");
        break;
    }
    
    return 0;
}