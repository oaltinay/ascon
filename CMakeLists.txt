cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_COMPILER "riscv64-unknown-elf-gcc")
set(CMAKE_CXX_COMPILER "riscv64-unknown-elf-g++")
set(CMAKE_ASM_COMPILER "riscv64-unknown-elf-gcc")

project (ascon)

set(CMAKE_C_FLAGS "-O0 -march=rv32i -mabi=ilp32")

include_directories(include)
file(GLOB SOURCES "src/*.c")
add_executable(ascon ${SOURCES})