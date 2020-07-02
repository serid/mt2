#include <stdlib.h>
#include <string.h>

#include "vec.h"

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
    "; Now print eax"
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
    "; end start\n";

const char* const CODE_TEMPLATE_END =
    "segment readable writeable\n"
    "\n"
    "output_buffer db 'eeeee',0xA\n"
    "output_buffer_size = $-output_buffer\n";

char* fasm_generate(void) {
    vec_str lines = vecNew_str();
    vecPush_str(&lines, "mov eax, 100\n");
    vecPush_str(&lines, "mov ebx, 5\n");
    vecPush_str(&lines, "add eax, ebx\n");

    size_t line_lens_sum = 0;
    vec_int line_lens = vecNewWithLen_int(lines.len);
    for (size_t i = 0; i < lines.len; i++) {
        size_t len = strlen(lines.mem[i]);
        line_lens_sum += len;
        line_lens.mem[i] = len;
    }

    vec_char result = vecNewWithLen_char(line_lens_sum);
    for (size_t i = 0, j = 0; i < lines.len; i++) {
        strcpy(&result.mem[j], lines.mem[i]);
        j += line_lens.mem[i];
    }

    vecDestroy_int(&line_lens);
    vecDestroy_str(&lines);

    return result.mem;  // Caller should free the string
}
