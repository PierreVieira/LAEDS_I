cmake_minimum_required(VERSION 3.15)
project(aeds1_tp2 C)

set(CMAKE_C_STANDARD 99)

add_executable(aeds1_tp2 main.c Headers/globais.h Headers/ordena.h Codigo/ordena.c Headers/auxiliar.h Codigo/auxiliar.c)