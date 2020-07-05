#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ir.h"
#include "panic.h"
#include "vec.h"

// TODO: allocate and free strings in fasm_generate
char* str_clone(char* str) {
    char* mem =
        assert_pnnull(malloc(strlen(str) + 1), "Unable to allocate string\n");
    return strcpy(mem, str);
}

// strcpy, no null terminator. Like strcpy, but omits null terminator.
void strcpy_nonnt(char* restrict dest, const char* restrict src) {
    size_t i = 0;
    while (src[i] != 0) {
        dest[i] = src[i];
        i++;
    }
}

const char* const CODE_TEMPLATE_START =
    "format ELF executable 3\n"
    "entry start\n"
    "\n"
    "segment readable executable\n"
    "\n"
    "include 'itoa.asm'\n"
    "\n"
    "start:\n"
    "mov eax,0\n"
    "call main\n"
    "; eax is proc result\n"
    "\n"
    "; Now print eax\n"
    "mov edi,output_buffer\n"
    "call itoa\n"
    "\n"
    "mov eax,4\n"
    "mov ebx,1\n"
    "mov ecx,output_buffer\n"
    "mov edx,output_buffer_size\n"
    "int 0x80\n"
    "\n"
    "mov eax,1\n"
    "xor ebx,ebx\n"
    "int 0x80 ; call exit\n"
    "; end start\n"
    "; PROCS:\n";

const char* const CODE_TEMPLATE_END =
    "; :PROCS\n"
    "segment readable writeable\n"
    "\n"
    "output_buffer db 'eeeee',0xA\n"
    "output_buffer_size = $-output_buffer\n";

vec_char fasm_generate(ir_Program program) {
    vec_str lines = vecNew_str();

    // CODE_TEMPLATE_START
    vecPush_str(&lines, str_clone(CODE_TEMPLATE_START));

    // Program
    for (size_t i = 0; i < program.procs.len; i++) {
        ir_Proc i_proc = program.procs.mem[i];

        // Proc header
        // <i_proc.name>:
        vecPush_str(&lines, str_clone(i_proc.name));
        vecPush_str(&lines, str_clone(":\n"));
        vecPush_str(&lines, str_clone("push ebp\n"));
        vecPush_str(&lines, str_clone("mov ebp, esp\n"));

        // Val is a variable only assigned once
        // i_proc.code.len is number of Vals

        for (size_t j = 0; j < i_proc.code.len; j++) {
            ir_IrItem item = i_proc.code.mem[j];
            size_t val_number = j + 1;
            switch (item.tag) {
                case IR_ITEM_TAG_INT_LIT: {
                    // move const to a Val
                    // mov dword [ebp-<val_number*4>], <item.data.int_lit>

                    // vecPush_str(&lines, "mov dword [ebp-");
                    // vecPush_str(&lines, sizeTtoa(val_number * 4));
                    // vecPush_str(&lines, "],");
                    // vecPush_str(&lines, u32toa(item.data.int_lit));
                    // vecPush_str(&lines, "\n");

                    // char* buffer = malloc(256);
                    // int result =
                    //     snprintf(buffer, 256, "mov dword [ebp-%zu],%u\n",
                    //              val_number * 4, item.data.int_lit);
                    // if (result > 256) {
                    //     fprintf(stderr, "Format result too big.\n");
                    //     exit(1);
                    // }

                    char* buffer;
                    assert_nm1(asprintf(&buffer, "mov dword [ebp-%zu], %u\n",
                                        val_number * 4, item.data.int_lit),
                               "Formatting error.\n");
                    vecPush_str(&lines, buffer);
                    break;
                }

                case IR_ITEM_TAG_FUNC_CALL: {
                    ir_FuncCall func = item.data.func_call;
                    // check builtin functions
                    if (strcmp(func.func_name, "add") == 0) {
                        // Builtin add
                        char* buffer;
                        // mov ebx, [ebp-arg1_valnum*4]\n
                        assert_nm1(asprintf(&buffer, "mov ebx, [ebp-%u]\n",
                                            func.arg1_valnum * 4),
                                   "Formatting error.\n");
                        vecPush_str(&lines, buffer);

                        // add ebx, [ebp-arg2_valnum*4]\n
                        assert_nm1(asprintf(&buffer, "add ebx, [ebp-%u]\n",
                                            func.arg2_valnum * 4),
                                   "Formatting error.\n");
                        vecPush_str(&lines, buffer);

                        // mov [ebp-val_number*4], ebx\n
                        assert_nm1(asprintf(&buffer, "mov [ebp-%zu], ebx\n",
                                            val_number * 4),
                                   "Formatting error.\n");
                        vecPush_str(&lines, buffer);
                    } else {
                        // Call func <func.func_name>
                        // TODO
                    }
                    break;
                }

                default:
                    panic("Unknown item.tag\n");
                    exit(1);
                    break;
            }
        }

        // Write last Val to eax
        char* buffer;
        // mov ebx, [ebp-arg1_valnum*4]\n
        assert_nm1(asprintf(&buffer, "mov eax, [ebp-%u]\n",
                     (i_proc.code.len - 1 + 1) * 4), "Formatting error.\n");
        vecPush_str(&lines, buffer);

        vecPush_str(&lines, str_clone("pop ebp\n"));
        vecPush_str(&lines, str_clone("ret\n"));
    }

    // CODE_TEMPLATE_END
    vecPush_str(&lines, str_clone(CODE_TEMPLATE_END));

    // Concatenate lines
    size_t line_lens_sum = 0;
    vec_sizeT line_lens = vecNewWithLen_sizeT(lines.len);
    for (size_t i = 0; i < lines.len; i++) {
        size_t len = strlen(lines.mem[i]);
        line_lens_sum += len;
        line_lens.mem[i] = len;
    }

    vec_char result = vecNewWithLen_char(line_lens_sum);
    for (size_t i = 0, j = 0; i < lines.len; i++) {
        strcpy_nonnt(&result.mem[j], lines.mem[i]);
        j += line_lens.mem[i];
    }

    // free lines
    for (size_t i = 0; i < lines.len; i++) {
        free(lines.mem[i]);
    }

    vecDestroy_sizeT(&line_lens);
    vecDestroy_str(&lines);

    return result;
}
