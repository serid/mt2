#pragma once
#include "ints.h"

#define TOK_LS 1
#define TOK_PROC 2
#define TOK_INT_LIT 3
#define TOK_IDENT 4
typedef struct {
    u8 tag;
    union internal {
        u32 int_lit;  // tag 3
        char* name; // tag 4
    } data;
} tok;
