#pragma once
#include <stdbool.h>

#include "vec_Tok.h"

bool compare_sub(char* str, char* sub);

vec_Tok tokenize(char* text);
