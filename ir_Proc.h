#ifndef IR_PROC_H
#define IR_PROC_H
#include "vec_ir_IrItem.h"
typedef struct {
    char *name;
    vec_ir_IrItem code;  // A list of SSA assignments
} ir_Proc;
#endif
