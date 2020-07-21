#include "vec.h"

#include <stdio.h>
#include <stdlib.h>

#include "ints.h"
#include "panic.h"
#include "vec_Tok.h"
#include "vec_ir_IrItem.h"
#include "vec_ir_Proc.h"
#include "vec_ir_StackItem.h"

#define generate_vec_c(TT, TS)                                                \
    vec_##TS vecNew_##TS() { return (vec_##TS){0, 0, NULL}; }                 \
    vec_##TS vecNewWithLen_##TS(size_t len) {                                 \
        TT *mem = assert_pnnull(malloc(len * sizeof(TT)),                      \
                               "Unable to allocate vec with len.\n");         \
        return (vec_##TS){len, len, mem};                                     \
    }                                                                         \
                                                                              \
    void _vecRecapacitate_##TS(vec_##TS *self, size_t capacity) {             \
        assert_ne(capacity, 0, "Recapacitate to 0 capacity is forbidden.\n"); \
                                                                              \
        TT *new_mem = assert_pnnull(realloc(self->mem, capacity * sizeof(TT)), \
                                   "Unable to resize vec.\n");                \
                                                                              \
        self->mem = new_mem;                                                  \
        self->_capacity = capacity;                                           \
    }                                                                         \
                                                                              \
    void vecResize_##TS(vec_##TS *self, size_t len) {                         \
        if (len > self->_capacity) {                                          \
            _vecRecapacitate_##TS(self, len * 2);                             \
        }                                                                     \
                                                                              \
        self->len = len;                                                      \
    }                                                                         \
                                                                              \
    void vecPush_##TS(vec_##TS *self, TT e) {                                 \
        vecResize_##TS(self, self->len + 1);                                  \
        self->mem[self->len - 1] = e;                                         \
    }                                                                         \
                                                                              \
    TT vecPop_##TS(vec_##TS *self) {                                          \
        TT popped = self->mem[self->len - 1];                                 \
        vecResize_##TS(self, self->len - 1);                                  \
        return popped;                                                        \
    }                                                                         \
                                                                              \
    void vecShrinkToFit_##TS(vec_##TS *self) {                                \
        _vecRecapacitate_##TS(self, self->len);                               \
    }                                                                         \
                                                                              \
    void vecDestroy_##TS(vec_##TS *self) { free(self->mem); }

generate_vec_c(size_t, sizeT);
generate_vec_c(char, char);
generate_vec_c(char *, str);

generate_vec_c(Tok, Tok)
generate_vec_c(ir_IrItem, ir_IrItem);
generate_vec_c(ir_Proc, ir_Proc)
generate_vec_c(ir_StackItem, ir_StackItem)
