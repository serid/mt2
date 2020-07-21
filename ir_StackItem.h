#pragma once
#include "ints.h"

#define IR_STACK_ITEM_INT_LIT 1
#define IR_STACK_ITEM_IDENT 2
typedef struct {
    u8 tag;
    union {
        u32 int_lit;  // tag IR_STACK_ITEM_INT_LIT
        char* name;   // tag IR_STACK_ITEM_IDENT

    } data;
} ir_StackItem;
