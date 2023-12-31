#pragma once

#ifndef __blowfish__
#define __blowfish__

#include <stdint.h>

class Blowfish {
public:
  void init(const unsigned char *key, int key_length);
  void Encrypt(unsigned char *plaintext, int length) const;
  void Decrypt(unsigned char *ciphertext, int length) const;

private:
  void EncryptBlock(uint32_t *left, uint32_t *right) const;
  void DecryptBlock(uint32_t *left, uint32_t *right) const;
  uint32_t Feistel(uint32_t value) const;

private:
  uint32_t parray_[18];
  uint32_t sbox_[4][256];
};

#endif /* defined(__blowfish__) */
