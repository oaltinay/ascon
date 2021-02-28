
#include "api.h"
#include "ascon.h"

#include <stdio.h>
#include <string.h>

static void print(unsigned char c, unsigned char* x, unsigned long long xlen) {
  unsigned long long i;
  printf("%c[%d]=", c, (int)xlen);
  for (i = 0; i < xlen; ++i) printf("%d, ", x[i]);
  printf("\n");
}

int main ()
{
  int result;
  unsigned long long alen = 0;
  unsigned long long mlen = 0;
  unsigned long long clen = 0;

  unsigned char a[] = "thisistheassociateddata.";
  unsigned char m[] = "thisisaplaintext";
  unsigned char c[strlen((const char*)m) + CRYPTO_ABYTES];
  unsigned char nsec[CRYPTO_NSECBYTES];
  unsigned char npub[CRYPTO_NPUBBYTES] = {"thisisthenonce."};
  unsigned char k[CRYPTO_KEYBYTES] = "thisisthekey.";   
  unsigned long cycle_end=0, cycle_start =0;
  int i;
  alen = strlen((const char*)a);
  mlen = strlen((const char*)m);
  clen = strlen((const char*)c);
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
  cycle_end=0; cycle_start =0;
  read_cycle(cycle_start);
  result |= crypto_aead_encrypt(c, &clen, m, mlen, a, alen, nsec, npub, k);
  read_cycle(cycle_end);
  printf("Encrypt %lu cycles\n", cycle_end-cycle_start);
 
  printf("Cipher Text\n");
  print('c', c, clen - CRYPTO_ABYTES);
  printf("\n");
  
  printf("Tag\n");
  print('t', c + clen - CRYPTO_ABYTES, CRYPTO_ABYTES);
  printf("\n");
  printf("Starting decryption...\n");
  cycle_end=0; cycle_start =0;
  read_cycle(cycle_start);
  result |= crypto_aead_decrypt(m, &mlen, nsec, c, clen, a, alen, npub, k);
  read_cycle(cycle_end); 
  printf("Decrypt %lu cycles\n", cycle_end-cycle_start); 

  printf("Associated data\n");
  print('a', a, alen);
  printf("\n");
  printf("Plain Text\n");
  print('m', m, mlen); 
  return 0;
}