#ifndef  ENCRYPT_DECRYPT_H_
#define  ENCRYPT_DECRYPT_H_

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
  u32 e;
  u32 o;
} u32_2;


#define read_cycle(cycle) asm volatile("rdcycle %0" : "=r" (cycle))
#define read_insn(insn) asm volatile("rdinstret %0" : "=r" (insn))

int crypto_aead_encrypt(unsigned char* c, unsigned long long* clen,
                        const unsigned char* m, unsigned long long mlen,
                        const unsigned char* ad, unsigned long long adlen,
                        const unsigned char* nsec, const unsigned char* npub,
                        const unsigned char* k);

int crypto_aead_decrypt(unsigned char* m, unsigned long long* mlen,
                        unsigned char* nsec, const unsigned char* c,
                        unsigned long long clen, const unsigned char* ad,
                        unsigned long long adlen, const unsigned char* npub,
                        const unsigned char* k);

void ROUND(u32 C_e, u32 C_o, u32* s_e, u32* s_o);

#endif // 