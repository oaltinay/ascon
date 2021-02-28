mkdir build
cd build
rm -rf *
cmake ..
make
spike --isa=RV32IMAFDC $RISCV/riscv32-unknown-elf/bin/pk ascon
