#include "vec.h"

#include <stdio.h>
#include <stdlib.h>

#define generate_vec_c(TT, TS)                                             \
    vec_##TS vecNew_##TS() { return (vec_##TS){0, 0, NULL}; }              \
                                                                           \
    void _vecRecapacitate_##TS(vec_##TS *self, size_t capacity) {          \
        if (capacity == 0) {                                               \
            fprintf(stderr, "Recapacitate to 0 capacity is forbidden.\n"); \
            return;                                                        \
        }                                                                  \
                                                                           \
        TT *new_mem = realloc(self->mem, capacity * sizeof(TT));           \
                                                                           \
        if (new_mem == NULL) {                                             \
            fprintf(stderr, "Unable to resize vec\n");                     \
            exit(1);                                                       \
        }                                                                  \
                                                                           \
        self->mem = new_mem;                                               \
        self->_capacity = capacity;                                        \
    }                                                                      \
                                                                           \
    void vecResize_##TS(vec_##TS *self, size_t len) {                      \
        if (len > self->_capacity) {                                       \
            _vecRecapacitate_##TS(self, len * 2);                          \
        }                                                                  \
                                                                           \
        self->len = len;                                                   \
    }                                                                      \
                                                                           \
    void vecPush_##TS(vec_##TS *self, TT e) {                              \
        vecResize_##TS(self, self->len + 1);                               \
        self->mem[self->len - 1] = e;                                      \
    }                                                                      \
                                                                           \
    TT vecPop_##TS(vec_##TS *self) {                                       \
        TT popped = self->mem[self->len - 1];                              \
        vecResize_##TS(self, self->len - 1);                               \
        return popped;                                                     \
    }                                                                      \
                                                                           \
    void vecShrinkToFit_##TS(vec_##TS *self) {                             \
        _vecRecapacitate_##TS(self, self->len);                            \
    }                                                                      \
                                                                           \
    void vecDestroy_##TS(vec_##TS *self) { free(self->mem); }

generate_vec_c(int, int);
generate_vec_c(char, char);
generate_vec_c(char*, str)
