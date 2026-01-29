#include <stdio.h>
#include <stdint.h>
#include "fixed_point.h"

int main(int argc, char **argv) {
    if (argc != 6) {
        printf("Usage: %s <x_raw> <a_raw> <b_raw> <c_raw> <q>\n", argv[0]);
        printf("All inputs must be integers. (x/a/b/c/q are int16 raw fixed-point values)\n");
        return 0;
    }

    // TODO
    int int_x, int_a, int_b, int_c, int_q;
    
    sscanf(argv[1], "%d", &int_x);
    sscanf(argv[2], "%d", &int_a);
    sscanf(argv[3], "%d", &int_b);
    sscanf(argv[4], "%d", &int_c);
    sscanf(argv[5], "%d", &int_q);

    int16_t x = (int16_t)int_x;
    int16_t a = (int16_t)int_a;
    int16_t b = (int16_t)int_b;
    int16_t c = (int16_t)int_c;
    int16_t q = (int16_t)int_q;

    eval_poly_ax2_minus_bx_plus_c_fixed(x, a, b, c, q);

    return 0;
}
