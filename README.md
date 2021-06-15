# Implementation of ASCON Cryptography Algorithm for RISCV ISA with GCC Built-ins

This repository implements Aston Cryptography algortihm for RISCV ISA. S-box operations are made with special RISC-V instructions(sbox).


## Prerequisites

  1. RISCV GNU Toolchain should be installed for riscv64-unknown-elf-gcc compiler
  2. Spike and pk should be installed for simulating compiled elf binary. (pk should be installed for RV32)
   
## Installation, Build and Run 

  Clone this repository.

  ```bash
  git clone git@github.com:oaltinay/ascon.git
  ```
  Go to repository.
  ```bash
  cd ascon
  ```
  Build and run.

  ```bash
  ./build_run.sh
  ```
