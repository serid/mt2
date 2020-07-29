#include <stdio.h>

int fib(int v1, int v2);

int main(void) {
    int v1;
    int v2;
    v1 = 35;
    v1 = fib(v1, v1);

    printf("%i\n", v1);
    return 0;
}

int funceq(int v1, int v2) {
    return v1 == v2;
}

int funcadd(int v1, int v2) {
    return v1 + v2;
}

int funcsub(int v1, int v2) {
    return v1 - v2;
}

int fib(int v1, int v2) {
    // Если v1 == 0, то v1000 = 0, выходим из функции
    int v1000;
    int v3;
    int v101;
    int v501;
    int v502;


    v1000 = 0;
    v2 = 0;
    v3 = funceq(v1, v2);
    if (v3)
        goto endFib;
        
    // Если v1 == 1, то v1000 = 1, выходим из функции
    v1000 = 1;
    v2 = 1;
    v3 = funceq(v1, v2);
    if (v3)
        goto endFib;
    
    
    // Иначе v1000 = funcadd(fib(v1 - 1), fib(v1 - 2)), выходим из функции
    v2 = 1;
    v101 = funcsub(v1, v2);
    v501 = fib(v101, v101);

    v2 = 2;
    v101 = funcsub(v1, v2);
    v502 = fib(v101, v101);
    
    v1000 = funcadd(v502, v501);
    
endFib:
    
    return v1000;
}
