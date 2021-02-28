#ifndef PERMUTATIONS_H_
#define PERMUTATIONS_H_

#include "endian.h"
#include "ascon.h"
#include <stdio.h>

#define EXT_BYTE64(x, n) ((u8)((u64)(x) >> (8 * (7 - (n)))))
#define INS_BYTE64(x, n) ((u64)(x) << (8 * (7 - (n))))

// Credit to Henry S. Warren, Hacker's Delight, Addison-Wesley, 2002
#define to_bit_interleaving(out, in)                          \
  do {                                                        \
    /*unsigned long cycle_end=0, cycle_start =0;*/\
    /*read_cycle(cycle_start);*/\
    u32 hi = (in) >> 32;                                      \
    u32 lo = (u32)(in);                                       \
    u32 r0, r1;                                               \
    r0 = (lo ^ (lo >> 1)) & 0x22222222, lo ^= r0 ^ (r0 << 1); \
    r0 = (lo ^ (lo >> 2)) & 0x0C0C0C0C, lo ^= r0 ^ (r0 << 2); \
    r0 = (lo ^ (lo >> 4)) & 0x00F000F0, lo ^= r0 ^ (r0 << 4); \
    r0 = (lo ^ (lo >> 8)) & 0x0000FF00, lo ^= r0 ^ (r0 << 8); \
    r1 = (hi ^ (hi >> 1)) & 0x22222222, hi ^= r1 ^ (r1 << 1); \
    r1 = (hi ^ (hi >> 2)) & 0x0C0C0C0C, hi ^= r1 ^ (r1 << 2); \
    r1 = (hi ^ (hi >> 4)) & 0x00F000F0, hi ^= r1 ^ (r1 << 4); \
    r1 = (hi ^ (hi >> 8)) & 0x0000FF00, hi ^= r1 ^ (r1 << 8); \
    (out).e = (lo & 0x0000FFFF) | (hi << 16);                 \
    (out).o = (lo >> 16) | (hi & 0xFFFF0000);                 \
    /*read_cycle(cycle_end);*/\
    /*printf("bit int %lu cycles\n", cycle_end-cycle_start);*/\
  } while (0)

// Credit to Henry S. Warren, Hacker's Delight, Addison-Wesley, 2002
#define from_bit_interleaving(out, in)                        \
  do {                                                        \
    u32 lo = ((in).e & 0x0000FFFF) | ((in).o << 16);          \
    u32 hi = ((in).e >> 16) | ((in).o & 0xFFFF0000);          \
    u32 r0, r1;                                               \
    r0 = (lo ^ (lo >> 8)) & 0x0000FF00, lo ^= r0 ^ (r0 << 8); \
    r0 = (lo ^ (lo >> 4)) & 0x00F000F0, lo ^= r0 ^ (r0 << 4); \
    r0 = (lo ^ (lo >> 2)) & 0x0C0C0C0C, lo ^= r0 ^ (r0 << 2); \
    r0 = (lo ^ (lo >> 1)) & 0x22222222, lo ^= r0 ^ (r0 << 1); \
    r1 = (hi ^ (hi >> 8)) & 0x0000FF00, hi ^= r1 ^ (r1 << 8); \
    r1 = (hi ^ (hi >> 4)) & 0x00F000F0, hi ^= r1 ^ (r1 << 4); \
    r1 = (hi ^ (hi >> 2)) & 0x0C0C0C0C, hi ^= r1 ^ (r1 << 2); \
    r1 = (hi ^ (hi >> 1)) & 0x22222222, hi ^= r1 ^ (r1 << 1); \
    out = (u64)hi << 32 | lo;                                 \
  } while (0)

#define P12()        \
  do {               \
    /*unsigned long cycle_end=0, cycle_start =0;*/\
    /*read_cycle(cycle_start);*/\
    ROUND(0xc, 0xc, s_e, s_o); \
    ROUND(0x9, 0xc, s_e, s_o); \
    ROUND(0xc, 0x9, s_e, s_o); \
    ROUND(0x9, 0x9, s_e, s_o); \
    ROUND(0x6, 0xc, s_e, s_o); \
    ROUND(0x3, 0xc, s_e, s_o); \
    ROUND(0x6, 0x9, s_e, s_o); \
    ROUND(0x3, 0x9, s_e, s_o); \
    ROUND(0xc, 0x6, s_e, s_o); \
    ROUND(0x9, 0x6, s_e, s_o); \
    ROUND(0xc, 0x3, s_e, s_o); \
    ROUND(0x9, 0x3, s_e, s_o); \
    /*read_cycle(cycle_end);*/\
    /*printf("ROUND %lu cycles\n", cycle_end-cycle_start);*/\
  } while (0)

#define P8()         \
  do {               \
    /*unsigned long cycle_end=0, cycle_start =0;*/\
    /*read_cycle(cycle_start);*/\
    ROUND(0x6, 0xc, s_e, s_o); \
    ROUND(0x3, 0xc, s_e, s_o); \
    ROUND(0x6, 0x9, s_e, s_o); \
    ROUND(0x3, 0x9, s_e, s_o); \
    ROUND(0xc, 0x6, s_e, s_o); \
    ROUND(0x9, 0x6, s_e, s_o); \
    ROUND(0xc, 0x3, s_e, s_o); \
    ROUND(0x9, 0x3, s_e, s_o); \
    /*read_cycle(cycle_end);*/\
    /*printf("p8 %lu cycles\n", cycle_end-cycle_start);*/\
  } while (0)

#define P6()         \
  do {               \
    ROUND(0x6, 0x9, s_e, s_o); \
    ROUND(0x3, 0x9, s_e, s_o); \
    ROUND(0xc, 0x6, s_e, s_o); \
    ROUND(0x9, 0x6, s_e, s_o); \
    ROUND(0xc, 0x3, s_e, s_o); \
    ROUND(0x9, 0x3, s_e, s_o); \
  } while (0)

#endif  // PERMUTATIONS_H_

