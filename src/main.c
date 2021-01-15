#include <stdio.h>
#include "api.h"
#include "encrypt_decrypt.h"

void print(unsigned char c, unsigned char* x, unsigned long long xlen) {
  unsigned long long i;
  printf("%c[%d]=", c, (int)xlen);
  for (i = 0; i < xlen; ++i) printf("%02x", x[i]);
  printf("\n");
}

int main ()
{
  int result;
  unsigned long long alen = 0;
  unsigned long long mlen = 0;
  unsigned long long clen = CRYPTO_ABYTES;
  unsigned char a[] = "ASCON";
  unsigned char m[] = "altinayaltinayalti";
  unsigned char c[strlen((const char*)m) + CRYPTO_ABYTES];
  unsigned char nsec[CRYPTO_NSECBYTES];
  unsigned char npub[CRYPTO_NPUBBYTES] = {0};
  unsigned char k[CRYPTO_KEYBYTES] = "ozlemozlemozlemo";
  alen = strlen((const char*)a);
  mlen = strlen((const char*)m);

  printf("Key\n");
  print('k', k, CRYPTO_KEYBYTES);

  printf("Nonce\n");
  print('n', npub, CRYPTO_NPUBBYTES);
  printf("\n");

  printf("Associated data\n");
  print('a', a, alen);

  printf("Plain Text\n");
  print('m', m, mlen);

  printf("Starting encryption...\n");
  result |= crypto_aead_encrypt(c, &clen, m, mlen, a, alen, nsec, npub, k);

  printf("Cipher Text\n");
  print('c', c, clen - CRYPTO_ABYTES);

  printf("Tag\n");
  print('t', c + clen - CRYPTO_ABYTES, CRYPTO_ABYTES);

  printf("Starting decryption...\n");
  result |= crypto_aead_decrypt(m, &mlen, nsec, c, clen, a, alen, npub, k);

  printf("Associated data\n");
  print('a', a, alen);

  printf("Plain Text\n");
  print('m', m, mlen);
  printf("\n");
  
  return 0;
}