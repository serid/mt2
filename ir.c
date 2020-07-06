#include "ir.h"

ir_Program compile(vec_tok toks) {
    ir_IrItem item;

    ir_Proc some_proc;
    some_proc.name = "main";
    some_proc.code = vecNew_ir_IrItem();

    item.var_num = 1;
    item.tag = 1;
    item.data.int_lit = 100;
    vecPush_ir_IrItem(&some_proc.code, item);
    item.var_num = 2;
    item.tag = 1;
    item.data.int_lit = 50;
    vecPush_ir_IrItem(&some_proc.code, item);
    item.var_num = 3;
    item.tag = 2;
    item.data.func_call = (ir_FuncCall){"add", 1, 2};
    vecPush_ir_IrItem(&some_proc.code, item);

    ir_Program program;

    program.procs = vecNew_ir_Proc();
    vecPush_ir_Proc(&program.procs, some_proc);

    return program;
}

void destroy_ir_Program(ir_Program* program) {
    for (size_t i = 0; i < program->procs.len; i++)
        destroy_ir_Proc(&program->procs.mem[i]);
    vecDestroy_ir_Proc(&program->procs);
}

void destroy_ir_Proc(ir_Proc* proc) {
    vecDestroy_ir_IrItem(&proc->code);
}
