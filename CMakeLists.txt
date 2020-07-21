cmake_minimum_required(VERSION 3.17)

project(MT2)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang")

add_executable(MT2 MT2.c vec.c vec.h panic.c panic.h util.c util.h
    tok.c tok.h tok_Tok.h vec_Tok.h fasm.c fasm.h ir.c ir.h ir_Proc.h ir_IrItem.h
    ir_StackItem.h vec_ir_StackItem.h vec_ir_Proc.h vec_ir_IrItem.h ints.h)
