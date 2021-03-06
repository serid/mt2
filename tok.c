#include "tok.h"

#include <stdio.h>

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

vec_Tok tokenize(char* text) {
    vec_Tok result = vecNew_Tok();
    for (size_t i = 0; text[i] != 0;) {
        if (text[i] == ' ') {
            i++;
            continue;
        }

        if (text[i] == '\n') {
            vecPush_Tok(&result, (Tok){.tag = TOK_LS});
            i += 1;
        } else if (text[i] == '=') {
            vecPush_Tok(&result, (Tok){.tag = TOK_ASSIGN});
            i += 1;
        } else if (text[i] == ':') {
            vecPush_Tok(&result, (Tok){.tag = TOK_LABEL});
            i += 1;
        } else if (text[i] == '?') {
            vecPush_Tok(&result, (Tok){.tag = TOK_MAYBE});
            i += 1;
        } else if (compare_sub(&text[i], "call")) {
            vecPush_Tok(&result, (Tok){.tag = TOK_CALL});
            i += 4;
        } else if (compare_sub(&text[i], "makeproc")) {
            vecPush_Tok(&result, (Tok){.tag = TOK_MAKEPROC});
            i += 8;
        } else if (isdigit(text[i])) {
            char* end;
            errno = 0;  // Do I need no zero it?
            long res = strtol(&text[i], &end, 10);
            if (errno == ERANGE) panic_errno("Int parse");
            vecPush_Tok(&result,
                        (Tok){.tag = TOK_INT_LIT, .data.int_lit = res});
            i += end - (text + i);
        } else if (text[i] == '$' && isdigit(text[i + 1])) {
            i++;

            char* end;
            errno = 0;  // Do I need no zero it?
            long res = strtol(&text[i], &end, 10);
            if (errno == ERANGE) panic_errno("Int parse");
            vecPush_Tok(&result,
                        (Tok){.tag = TOK_VAR_NUM, .data.var_num = res});
            i += end - (text + i);
        } else if (isalpha(text[i])) {
            vec_char name = vecNew_char();
            for (; isalpha(text[i]); i++) vecPush_char(&name, text[i]);
            vecPush_char(&name, '\0');

            vecPush_Tok(&result,
                        (Tok){.tag = TOK_IDENT, .data.name = name.mem});
        } else {
            fputs("Unknown token.\n", stderr);
            exit(1);
        }
    }
    return result;
}
