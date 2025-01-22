cmake_minimum_required(VERSION 3.30)
project(FBCFBR C)

set(CMAKE_C_STANDARD 11)

add_executable(FBCFBR main.c
        lexer.c
        lexer.h)
