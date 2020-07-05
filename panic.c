#include "panic.h"

#include <stdio.h>
#include <stdlib.h>

void panic(char* msg) {
    fputs(msg, stderr);
    exit(1);
}

void panic_errno(char* msg) {
    perror(msg);
    exit(1);
}

// assert not equal
int assert_ne(int v, int antiexpected, char* msg) {
    if (v == antiexpected) {
        panic(msg);
        return 666;  // Unreachable
    } else
        return v;
}

// assert not equal and errno
int assert_ne_errno(int v, int antiexpected, char* msg) {
    if (v == antiexpected) {
        panic_errno(msg);
        return 666;  // Unreachable
    } else
        return v;
}

// assert not equal to -1
int assert_nm1(int v, char* msg) { return assert_ne(v, -1, msg); }

// assert not equal to -1 and errno
int assert_nm1_errno(int v, char* msg) { return assert_ne_errno(v, -1, msg); }

// assert pointer not equal to NULL
void* assert_pnnull(void* v, char* msg) {
    if (v == NULL) {
        panic(msg);
        return (void*)666;  // Unreachable
    } else
        return v;
}

// assert pointer not equal to -1
void* assert_pnm1(void* v, char* msg) {
    if (v == (void*)-1) {
        panic(msg);
        return (void*)666;  // Unreachable
    } else
        return v;
}

// assert pointer not equal to -1 and errno
void* assert_pnm1_errno(void* v, char* msg) {
    if (v == (void*)-1) {
        panic_errno(msg);
        return (void*)666;  // Unreachable
    } else
        return v;
}
