#include "ascon.h"

#define ROTR32(x, n) (((x) >> (n)) | ((x) << (32 - (n))))

void ROUND(u32 C_e, u32 C_o, u32* s_e, u32* s_o) 
{
  unsigned long cycle_end=0, cycle_start =0;

  u32_2 t0, t1, t2, t3, t4;
  /* round constant */ 
  s_e[2] ^= C_e;                      s_o[2] ^= C_o; 
  /* s-box layer */ 
  read_insn(cycle_start);
  //__builtin_riscv_sbox(s_e, 1);
  //__builtin_riscv_sbox(s_o, 1); 
  s_e[0] ^= s_e[4];                  s_o[0] ^= s_o[4];
  s_e[4] ^= s_e[3];                  s_o[4] ^= s_o[3];
  s_e[2] ^= s_e[1];                  s_o[2] ^= s_o[1];
  t0.e = s_e[0];                     t0.o = s_o[0];
  t4.e = s_e[4];                     t4.o = s_o[4];
  t3.e = s_e[3];                     t3.o = s_o[3];
  t1.e = s_e[1];                     t1.o = s_o[1];
  t2.e = s_e[2];                     t2.o = s_o[2];
  s_e[0] = t0.e ^ (~t1.e & t2.e);    s_o[0] = t0.o ^ (~t1.o & t2.o);
  s_e[2] = t2.e ^ (~t3.e & t4.e);    s_o[2] = t2.o ^ (~t3.o & t4.o);
  s_e[4] = t4.e ^ (~t0.e & t1.e);    s_o[4] = t4.o ^ (~t0.o & t1.o);
  s_e[1] = t1.e ^ (~t2.e & t3.e);    s_o[1] = t1.o ^ (~t2.o & t3.o);
  s_e[3] = t3.e ^ (~t4.e & t0.e);    s_o[3] = t3.o ^ (~t4.o & t0.o);
  s_e[1] ^= s_e[0];                  s_o[1] ^= s_o[0]; 
  s_e[3] ^= s_e[2];                  s_o[3] ^= s_o[2]; 
  s_e[0] ^= s_e[4];                  s_o[0] ^= s_o[4];
  /*linear layer */
  read_insn(cycle_start); 
  t0.e  = s_e[0] ^ ROTR32(s_o[0], 4);   t0.o  = s_o[0] ^ ROTR32(s_e[0], 5); 
  t1.e  = s_e[1] ^ ROTR32(s_e[1], 11);  t1.o  = s_o[1] ^ ROTR32(s_o[1], 11); 
  t2.e  = s_e[2] ^ ROTR32(s_o[2], 2);   t2.o  = s_o[2] ^ ROTR32(s_e[2], 3); 
  t3.e  = s_e[3] ^ ROTR32(s_o[3], 3);   t3.o  = s_o[3] ^ ROTR32(s_e[3], 4); 
  t4.e  = s_e[4] ^ ROTR32(s_e[4], 17);  t4.o  = s_o[4] ^ ROTR32(s_o[4], 17); 
  s_e[0] ^=  ROTR32(t0.o, 9);           s_o[0] ^= ROTR32(t0.e, 10); 
  s_e[1] ^=  ROTR32(t1.o, 19);          s_o[1] ^= ROTR32(t1.e, 20); 
  s_e[2] ^= t2.o;                                    s_o[2] ^= ROTR32(t2.e, 1); 
  s_e[3] ^= ROTR32(t3.e, 5);            s_o[3] ^= ROTR32(t3.o, 5); 
  s_e[4] ^= ROTR32(t4.o, 3);            s_o[4] ^= ROTR32(t4.e, 4); 
  s_e[2] = ~s_e[2];                                  s_o[2] = ~s_o[2]; 
}