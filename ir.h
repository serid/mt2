#pragma once
#include "ints.h"
#include "vec_ir_Proc.h"
// Program is a list of procedures
// Procedure is a name and a list of SSA assignments
// SSA assignment is a function call or const move
typedef struct {
    vec_ir_Proc procs;
} ir_Program;
