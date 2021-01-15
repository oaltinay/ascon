cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_COMPILER "riscv64-unknown-elf-gcc")
set(CMAKE_CXX_COMPILER "riscv64-unknown-elf-g++")
set(CMAKE_ASM_COMPILER "riscv64-unknown-elf-gcc")

project (ascon)

set(CMAKE_C_FLAGS "-march=rv32imafdc -mabi=ilp32")
#Bring the headers into the project
include_directories(include)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")
 
add_executable(ascon_encrypt ${SOURCES})