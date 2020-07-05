. compile.sh &&
./build/MT2 teet/out.asm &&
fasm teet/out.asm teet/bin &&
./teet/bin && (
    rm -f teet/bin
    rm -f teet/out.asm
)
