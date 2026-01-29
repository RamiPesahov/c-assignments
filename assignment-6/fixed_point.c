#include "fixed_point.h"
#include <stdio.h>

#define CONVERT_TO_DECIMAL 1000000

void print_fixed(int16_t raw, int16_t q) {
    // TODO: Print up to 6 decimal places (with truncation)
    
    if (raw < 0) {
        printf("-");
        raw = -raw;
    }
    int16_t integer_part = (raw >> q);
    int16_t mask = (1 << q) - 1;
    uint16_t fraction_raw = (raw & mask);

    uint32_t decimal_part = ((uint64_t)fraction_raw * CONVERT_TO_DECIMAL) >> q;

    printf("%d.%06u", integer_part, decimal_part);

}

int16_t add_fixed(int16_t a, int16_t b) {
    // TODO: Implement addition
     
    return (a + b);
}

int16_t subtract_fixed(int16_t a, int16_t b) {
    // TODO: Implement subtraction

    return (a - b);
}

int16_t multiply_fixed(int16_t a, int16_t b, int16_t q) {
    // TODO: Implement fixed-point multiply:
       //- Use a wider type for intermediate multiplication (e.g., int32_t or int64_t).

       int64_t intermidiate = ((int64_t)a * (int64_t)b);
       return (int16_t) (intermidiate >> q);
}

void eval_poly_ax2_minus_bx_plus_c_fixed(int16_t x, int16_t a, int16_t b, int16_t c, int16_t q) {
    /* TODO:
       Evaluate: y = a*x^2 - b*x + c
    */

    int16_t x2 = multiply_fixed(x, x, q);
    int16_t ax2 = multiply_fixed(a, x2, q);
    int16_t bx = multiply_fixed(b, x, q);
    int16_t y = add_fixed(subtract_fixed(ax2, bx), c);
   
    printf("the polynomial output for a=");
    print_fixed(a, q);
    printf(", b=");
    print_fixed(b, q);
    printf(", c=");
    print_fixed(c, q);
    printf(" is ");
    /* TODO: print y once computed */
    /* print_fixed(y, q); */
    print_fixed(y, q);
}
