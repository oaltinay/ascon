#ifndef READ_CSR_H_
#define READ_CSR_H_

#define read_cycle(cycle) asm volatile("rdcycle %0" : "=r" (cycle));
#define read_insn(insn) asm volatile("rdinstret %0" : "=r" (insn));

#endif