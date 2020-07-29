. compile.sh &&
./build/MT2 teet/inp.mt2 teet/out.asm && (
    cat teet/out.asm
    rm -f teet/out.asm
)
