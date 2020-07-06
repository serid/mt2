#include "tok.h"

#include "ctype.h"
#include "errno.h"
#include "panic.h"

bool compare_sub(char* str, char* sub) {
    while (true) {
        if (*sub == 0) return true;
        if (*str == 0) return false;
        if (*str != *sub) return false;
        str++;
        sub++;
    }
}

vec_tok tokenize(char* text) {
    vec_tok result = vecNew_tok();
    for (size_t i = 0; text[i] != 0;) {
        if (text[i] == ' ') {
            i++;
            continue;
        }

        if (text[i] == '\n') {
            vecPush_tok(&result, (tok){.tag = 1});
            i += 1;
        } else if (compare_sub(&text[i], "proc")) {
            vecPush_tok(&result, (tok){.tag = 2});
            i += 4;
        } else if (isdigit(text[i])) {
            char* end;
            errno = 0;  // Do I need no zero it?
            long res = strtol(&text[i], &end, 10);
            if (errno == ERANGE) panic_errno("Int parse");
            vecPush_tok(&result, (tok){.tag = 3, .data.int_lit = res});
            i += end - (text + i);
        } else {
            // TODO: identifiers
            vecPush_tok(&result, (tok){.tag = 0});
            i++;
        }
    }
    return result;
}
