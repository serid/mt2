#include <inttypes.h>
#include <stdio.h>

#include "fasm.h"

int main(void) {
    puts("Hello, world!");

    puts(fasm_generate());

    // vec_sizeT vec1 = vecNew_sizeT();
    // vecPush_sizeT(&vec1, 100);
    // vecPush_sizeT(&vec1, 200);
    // printf("%"PRIi32"\n", vecPop_sizeT(&vec1));
    // printf("%"PRIi32"\n", vecPop_sizeT(&vec1));

    // vec_float vec2 = vecNew_float();
    // vecPush_float(&vec2, 100);
    // vecPush_float(&vec2, 200);
    // printf("%f\n", vecPop_float(&vec2));
    // printf("%f\n", vecPop_float(&vec2));

    return 0;
}
