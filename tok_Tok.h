#pragma once
#include "ints.h"

#define TOK_LS 1
#define TOK_MAKEPROC 2
#define TOK_CALL 3
#define TOK_ASSIGN 4
#define TOK_INT_LIT 5
#define TOK_IDENT 6
#define TOK_VAR_NUM 7
typedef struct {
    u8 tag;
    union {
        u32 int_lit;  // tag TOK_INT_LIT
        char* name;   // tag TOK_IDENT
        u32 var_num;   // tag TOK_VAR_NUM
    } data;
} Tok;
