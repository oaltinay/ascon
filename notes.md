## to_bit_interleaving() function --> 340 cycle
r0 = (lo ^ (lo >> 1)) & 0x22222222, lo ^= r0 ^ (r0 << 1) --> 17 clock cycle 

## ROUND() function --> 289 cycle
 x2.o = t2.o ^ (~t3.o & t4.o); --> 9 clock cycle


```
    unsigned long cycle_end, cycle_start; \
    read_cycle(cycle_start);  \    
    read_cycle(cycle_end);                                  \
    printf("Test::Took %lu cycles in for ROUND() function.\n", cycle_end - cycle_start);\
```

