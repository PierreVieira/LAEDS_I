cmake_minimum_required(VERSION 3.14)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c Headers/globais.h "C files/pegar_do_arquivo.c" Headers/pegar_do_arquivo.h Headers/guloso_solution.h "C files/guloso_solution.c" Headers/bruto_solution.h "C files/bruto_solution.c" "C files/gettimeofday.c" Headers/gettimeofday.h "C files/getrusage.c" Headers/getrusage.h)