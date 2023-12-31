#pragma once

#ifndef __blowfish__
#define __blowfish__

#include <stdint.h>

class Blowfish {
public:
  Blowfish(const unsigned char *key, int key_length);
  void init(const unsigned char *key, int key_length);
  void encrypt(unsigned char *plaintext, int length) const;
  void decrypt(unsigned char *ciphertext, int length) const;

private:
  void blockEncrypt(uint32_t *left, uint32_t *right) const;
  void blockDecrypt(uint32_t *left, uint32_t *right) const;
  uint32_t feistel(uint32_t value) const;

private:
  uint32_t parray_[18];
  uint32_t sbox_[4][256];
};

#endif /* defined(__blowfish__) */
