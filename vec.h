#ifndef VEC_H
#define VEC_H
#include <stdlib.h>

#include "ints.h"

#define generate_vec_h(TT, TS)                                    \
    typedef struct {                                              \
        u32 len;                                                  \
        u32 _capacity;                                            \
        TT *mem;                                                  \
    } vec_##TS;                                                   \
                                                                  \
    vec_##TS vecNew_##TS();                                       \
                                                                  \
    vec_##TS vecNewWithLen_##TS(size_t len);                      \
                                                                  \
    void vecResize_##TS(vec_##TS *v, size_t new_len);             \
                                                                  \
    void _vecRecapacitate_##TS(vec_##TS *v, size_t new_capacity); \
                                                                  \
    void vecPush_##TS(vec_##TS *v, TT e);                         \
                                                                  \
    TT vecPop_##TS(vec_##TS *v);                                  \
                                                                  \
    void vecShrinkToFit_##TS(vec_##TS *v);                        \
                                                                  \
    void vecDestroy_##TS(vec_##TS *v);

generate_vec_h(size_t, sizeT);
generate_vec_h(char, char);
generate_vec_h(char *, str)
#endif
