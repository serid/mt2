#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <unistd.h>

#include "fasm.h"
#include "ir.h"
#include "panic.h"

void write_bytes(char* filename, vec_char* bytes) {
    int fd = assert_nm1_errno(open("out.fasm", O_RDWR | O_CREAT | O_TRUNC,
                                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH),
                              "File creation failed");
    if (write(fd, bytes->mem, bytes->len) != bytes->len) {
        panic_errno("File write");
    }
    close(fd);
}

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

    vec_char compiled_code = fasm_generate(program);
    write_bytes("out.fasm", &compiled_code);
    vecDestroy_char(&compiled_code);

    return 0;
}
