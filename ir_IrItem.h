#pragma once
#include "ints.h"
typedef struct {
    char* func_name;
    u32 arg1_varnum;
    u32 arg2_varnum;
} ir_FuncCall;

#define IR_ITEM_TAG_INT_LIT 1
#define IR_ITEM_TAG_FUNC_CALL 2
typedef struct  // Assignment
{
    u16 var_num;
    u8 tag;
    union {
        u32 int_lit;
        ir_FuncCall func_call;
    } data;
} ir_IrItem;
