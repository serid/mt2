#pragma once
#include "ints.h"
#include "vec_ir_Proc.h"
#include "vec_Tok.h"
// Program is a list of procedures.
// Procedure is a name and a list of assignments.
// Assignment argument is a VarNum (variable number) and a (function call or
// const).
typedef struct {
    vec_ir_Proc procs;
} ir_Program;

ir_Program compile(vec_Tok toks);

void destroy_ir_Program(ir_Program* program);
