#include <stdio.h>

#include "fasm.h"
#include "ir.h"
#include "panic.h"
#include "tok.h"
#include "util.h"

int main(int argc, char* argv[]) {
    puts("Hello, world!");

    if (argc < 2) {
        fputs("Usage: MT2 [OUTPUT_FILE_NAME]\n", stderr);
        exit(1);
    }

    vec_tok toks = tokenize("proc proc 1000 aa");

    // Print tokens
    for (size_t i = 0; i < toks.len; i++) printf("%i,", toks.mem[i].tag);
    putc('\n', stdout);

    ir_Program program = compile(toks);

    vecDestroy_tok(&toks);

    vec_char compiled_code = fasm_generate(program);
    write_bytes(argv[1], &compiled_code);
    vecDestroy_char(&compiled_code);

    destroy_ir_Program(&program);

    return 0;
}
