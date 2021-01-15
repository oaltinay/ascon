# Implementation of Aston Cryptography Algorithm for RISCV ISA

This repository implements Aston Cryptography algortihm for RISCV ISA.

## Prerequisites

  1. RISCV GNU Toolchain should be installed for riscv64-unknown-elf-gcc compiler
  2. Spike and pk should be installed for simulating compiled elf binary. (pk should be installed for RV32)
   
## Installation and Build

  Clone this repository.

  ```bash
  git clone git@github.com:oaltinay/ascon.git
  ```
  Go to repo path and create build directory.
  ```bash
  cd /path/to/repo
  mkdir build
  cd build
  ```
  Create make file for project with cmake.
  ```bash
  cmake ..
  ``` 
  Build project.
  ```bash
  make
  ``` 

### Run 
  
  Since compiled binary is RISCV32 elf, to run this project on Ubuntu Spike and 32-bit pk should be installed.
  ```bash
  spike --isa=RV32IMAFDC /opt/riscv/riscv32-unknown-elf/bin/pk ascon_encrypt
  ```
