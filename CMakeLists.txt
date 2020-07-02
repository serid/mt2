cmake_minimum_required(VERSION 3.17)

project(MT2)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang")

add_executable(MT2 MT2.c vec.c vec.h fasm.c fasm.h ints.h)
