#include "panic.h"

#include <stdio.h>
#include <stdlib.h>

void panic(char* msg) {
    fputs(msg, stderr);
    exit(1);
}

int assert_ne(int v, int antiexpected, char* msg) {
    if (v == antiexpected) {
        panic(msg);
        return 666;  // Unreachable
    } else
        return v;
}

int assert_nm1(int v, char* msg) { return assert_ne(v, -1, msg); }

void* assert_nnull(void* v, char* msg) {
    if (v == NULL) {
        panic(msg);
        return (void*)666;  // Unreachable
    } else
        return v;
}
