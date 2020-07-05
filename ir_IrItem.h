#pragma once
#include "ints.h"
typedef struct {
    char* func_name;
    u32 arg1_valnum;
    u32 arg2_valnum;
} ir_FuncCall;

#define IR_ITEM_TAG_INT_LIT 1
#define IR_ITEM_TAG_FUNC_CALL 2
typedef struct  // Operators that may be called in SSassignment
{
    u8 tag;
    union {
        u32 int_lit;
        ir_FuncCall func_call;
    } data;
} ir_IrItem;
