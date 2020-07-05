#pragma once
#include "vec_ir_IrItem.h"
typedef struct {
    char* name;
    vec_ir_IrItem code;  // A list of SSA assignments
} ir_Proc;

void destroy_ir_Proc(ir_Proc* proc);
