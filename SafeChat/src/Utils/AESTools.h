//
// Created by hanyang on 2024/5/1.
// a class use crypto++ to use AES

#ifndef SAFECHAT_AESTOOL_H
#define SAFECHAT_AESTOOL_H

#include<string>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>


class AESTool {
public:
    static std::string AES_encrypt(const std::string &plaintext, const std::string &key);

    static std::string AES_decrypt(const std::string &ciphertext, const std::string &key);
};


#endif //SAFECHAT_AESTOOL_H
