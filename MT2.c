#include <inttypes.h>
#include <stdio.h>

#include "fasm.h"
#include "ir.h"

int main(void) {
    puts("Hello, world!");

    ir_IrItem item;

    ir_Proc some_proc;
    some_proc.name = "main";
    some_proc.code = vecNew_ir_IrItem();

    item.tag = 1;
    item.data.int_lit = 100;
    vecPush_ir_IrItem(&some_proc.code, item);
    item.tag = 1;
    item.data.int_lit = 50;
    vecPush_ir_IrItem(&some_proc.code, item);
    item.tag = 2;
    item.data.func_call = (ir_FuncCall){"add", 1, 2};
    vecPush_ir_IrItem(&some_proc.code, item);

    ir_Program program;
    program.procs = vecNew_ir_Proc();
    vecPush_ir_Proc(&program.procs, some_proc);

    puts(fasm_generate(program));
    
    // TODO: write output to file

    return 0;
}
