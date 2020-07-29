. compile.sh &&
./build/MT2 teet/out.asm && (
    cat teet/out.asm
    rm -f teet/out.asm
)
