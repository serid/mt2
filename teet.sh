. compile.sh &&
./build/MT2 teet/out &&
fasm teet/out teet/bin &&
./teet/bin && (
    rm -f teet/bin
    rm -f teet/out
)
