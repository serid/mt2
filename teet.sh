. compile.sh &&
./build/MT2 teet/inp.mt2 teet/out.asm &&
fasm teet/out.asm teet/bin &&
./teet/bin && (
    rm -f teet/bin
    rm -f teet/out.asm
)
