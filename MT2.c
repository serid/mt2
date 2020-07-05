#include <stdio.h>

#include "fasm.h"
#include "ir.h"
#include "panic.h"
#include "util.h"

int main(int argc, char* argv[]) {
    puts("Hello, world!");

    if (argc < 2)
    {
        fputs("Usage: MT2 [OUTPUT_FILE_NAME]\n", stderr);
        exit(1);
    }

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

    vec_char compiled_code = fasm_generate(program);
    write_bytes(argv[1], &compiled_code);
    vecDestroy_char(&compiled_code);

    vecDestroy_ir_IrItem(&some_proc.code);
    vecDestroy_ir_Proc(&program.procs);

    return 0;
}
