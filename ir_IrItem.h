#pragma once
#include "ints.h"
typedef struct {
    char* func_name;
    u32 var_num;
    u32 arg1_varnum;
    u32 arg2_varnum;
} ir_FuncCall;

typedef struct {
    u32 var_num;
    u32 int_lit;
} ir_ConstAssign;

#define IR_ITEM_TAG_CONST_ASSIGN 1
#define IR_ITEM_TAG_FUNC_CALL 2
typedef struct {
    u8 tag;
    union {
        ir_ConstAssign const_assign;  // tag IR_ITEM_TAG_CONST_ASSIGN
        ir_FuncCall func_call;        // tag IR_ITEM_TAG_FUNC_CALL
    } data;
} ir_IrItem;

void destroy_ir_IrItem(ir_IrItem* item);
