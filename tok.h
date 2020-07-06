#pragma once
#include <stdbool.h>

#include "vec_tok.h"

bool compare_sub(char* str, char* sub);

vec_tok tokenize(char* text);
