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

    vec_Tok toks = tokenize(
        "$0 100 =\n"
        "$1 50 =\n"
        "$2 $0 $1 add call\n"
        "main makeproc\n");

    // Print tokens
    for (size_t i = 0; i < toks.len; i++) printf("%i,", toks.mem[i].tag);
    putc('\n', stdout);

    ir_Program program = compile(toks);

    for (size_t i = 0; i < toks.len; i++)
    {
        if (toks.mem[i].tag == TOK_IDENT)
            free(toks.mem[i].data.name);
    }
    
    vecDestroy_Tok(&toks);

    vec_char compiled_code = fasm_generate(program);
    write_bytes(argv[1], &compiled_code);
    vecDestroy_char(&compiled_code);

    destroy_ir_Program(&program);

    return 0;
}
