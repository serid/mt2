#include <inttypes.h>
#include <stdio.h>

#include "fasm.h"

int main(void) {
    puts("Hello, world!");

    puts(fasm_generate());

    // vec_int vec1 = vecNew_int();
    // vecPush_int(&vec1, 100);
    // vecPush_int(&vec1, 200);
    // printf("%"PRIi32"\n", vecPop_int(&vec1));
    // printf("%"PRIi32"\n", vecPop_int(&vec1));

    // vec_float vec2 = vecNew_float();
    // vecPush_float(&vec2, 100);
    // vecPush_float(&vec2, 200);
    // printf("%f\n", vecPop_float(&vec2));
    // printf("%f\n", vecPop_float(&vec2));

    return 0;
}
