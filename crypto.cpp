#include <string.h>
#include "crypto.h"

uint8_t aes[AES_BLOCK_SIZE]; // AES-256 key
AES_KEY enc_key;
AES_KEY dec_key;

RSA* loadPUBLICKeyFromString( const char* publicKeyStr )
{
    BIO* bio = BIO_new_mem_buf( (void *)publicKeyStr, -1 ) ; // -1: assume string is null terminated

    // Load the RSA key from the BIO
    RSA* rsaPubKey = PEM_read_bio_RSAPublicKey(bio, NULL, NULL, NULL);

    if( !rsaPubKey )
        printf( "ERROR: Could not load PUBLIC KEY!  PEM_read_bio_RSA_PUBKEY FAILED: %s\n", ERR_error_string( ERR_get_error(), NULL ) ) ;

    BIO_free( bio );
    return rsaPubKey;
}
