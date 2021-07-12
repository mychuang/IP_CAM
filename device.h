#ifndef DEVICE_H
#define DEVICE_H
#include <QString>
#include <openssl/rsa.h>
#include <openssl/aes.h>

struct Device {
    uint8_t mac[6];
    QString name;
    QString model;
    QString ip;

    RSA *pKey;
    uint8_t iv[AES_BLOCK_SIZE]; // AES initializtion vector
    bool aes_ready;

    QString username;
    QString password;

    bool dhcp;
    QString netmask;
    QString gateway;
};

//extern Device *selected_dev;
#endif // DEVICE_H
