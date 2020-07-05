#include "util.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "panic.h"

char* str_clone(char* str) {
    char* mem =
        assert_pnnull(malloc(strlen(str) + 1), "Unable to allocate string\n");
    return strcpy(mem, str);
}

// strcpy, no null terminator. Like strcpy, but omits null terminator.
void strcpy_nonnt(char* restrict dest, const char* restrict src) {
    size_t i = 0;
    while (src[i] != 0) {
        dest[i] = src[i];
        i++;
    }
}

void write_bytes(char* filename, vec_char* bytes) {
    int fd = assert_nm1_errno(open(filename, O_RDWR | O_CREAT | O_TRUNC,
                                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH),
                              "File creation failed");
    if (write(fd, bytes->mem, bytes->len) != bytes->len) {
        panic_errno("File write");
    }
    close(fd);
}
