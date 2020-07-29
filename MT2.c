#include <stdio.h>

#include "fasm.h"
#include "ir.h"
#include "panic.h"
#include "tok.h"
#include "util.h"

int main(int argc, char* argv[]) {
    puts("Hello, world!");

    if (argc < 3) {
        fputs("Usage: MT2 INPUT_FILE_NAME OUTPUT_FILE_NAME\n", stderr);
        exit(1);
    }

    vec_char input = read_bytes(argv[1]);
    vecPush_char(&input, '\0');

    vec_Tok toks = tokenize(input.mem);

    vecDestroy_char(&input);

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
    write_bytes(argv[2], &compiled_code);
    vecDestroy_char(&compiled_code);

    destroy_ir_Program(&program);

    return 0;
}
