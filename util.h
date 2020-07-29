#include "vec.h"

char* str_clone(const char* str);

void strcpy_nonnt(char* restrict dest, const char* restrict src);

void write_bytes(char* filename, vec_char* bytes);

vec_char read_bytes(char* filename);
