. compile.sh &&
./build/MT2 teet/inp.mt2 teet/out.asm &&
fasm teet/out.asm teet/bin &&
valgrind ./teet/bin && (
    rm -f teet/bin
    rm -f teet/out.asm
)
