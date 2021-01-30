
#include "api.h"
#include "encrypt_decrypt.h"

#include <stdio.h>
#include <string.h>

void print(unsigned char c, unsigned char* x, unsigned long long xlen) {
  unsigned long long i;
  printf("%c[%d]=", c, (int)xlen);
  for (i = 0; i < xlen; ++i) printf("%c", x[i]);
  printf("\n");
}

int main ()
{
  int result;
  unsigned long long alen = 0;
  unsigned long long mlen = 0;
  unsigned long long clen = 0;

  unsigned char a[] = "ASCON";
  unsigned char m[] = "altinayaltinayal";
  unsigned char c[strlen((const char*)m) + CRYPTO_ABYTES];
  unsigned char nsec[CRYPTO_NSECBYTES];
  unsigned char npub[CRYPTO_NPUBBYTES] = {0};
  unsigned char k[CRYPTO_KEYBYTES] = "ozlemozlemozlemo";               

  alen = strlen((const char*)a);
  mlen = strlen((const char*)m);

  printf("\nKey\n");
  print('k', k, CRYPTO_KEYBYTES);
  printf("\n");

  printf("Nonce\n");
  print('n', npub, CRYPTO_NPUBBYTES);
  printf("\n");

  printf("Associated data\n");
  print('a', a, alen);
  printf("\n");

  printf("Plain Text\n");
  print('m', m, mlen);
  printf("\n");

  printf("Starting encryption...\n");
          unsigned long cycle_end, cycle_start;  \
          read_cycle(cycle_start);\

  result |= crypto_aead_encrypt(c, &clen, m, mlen, a, alen, nsec, npub, k);
                      read_cycle(cycle_end); \
      printf("Test::Took %lu cycles in function.\n", cycle_end - cycle_start); \
  printf("Cipher Text\n");
  print('c', c, clen - CRYPTO_ABYTES);
  printf("\n");
  
  printf("Tag\n");
  print('t', c + clen - CRYPTO_ABYTES, CRYPTO_ABYTES);
  printf("\n");
  
  printf("Starting decryption...\n");
  result |= crypto_aead_decrypt(m, &mlen, nsec, c, clen, a, alen, npub, k);

  printf("Associated data\n");
  print('a', a, alen);
  printf("\n");
  printf("Plain Text\n");
  print('m', m, mlen);
  printf("\n");
  
  return 0;
}