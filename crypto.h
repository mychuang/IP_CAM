#ifndef CRYPTO_H
#define CRYPTO_H
#include <stdint.h>
#include <openssl/rsa.h>
#include <openssl/aes.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/err.h>

inline unsigned int size_with_padding(unsigned int n)
{
    return (n & 0xfff0) + ((n & 0x0f) ? 16 : 0);
}

RSA* loadPUBLICKeyFromString( const char* publicKeyStr );

extern uint8_t aes[AES_BLOCK_SIZE]; // AES-256 key
extern AES_KEY enc_key;
extern AES_KEY dec_key;

#endif // CRYPTO_H
