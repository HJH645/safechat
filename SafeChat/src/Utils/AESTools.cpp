//
// Created by hanyang on 2024/5/1.
//

#include "AESTools.h"


std::string AESTool::AES_encrypt(const std::string &plaintext, const std::string &key) {
    std::string ciphertext;

    // AES加密
    CryptoPP::AES::Encryption aesEncryption((unsigned char *) key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (unsigned char *) key.c_str());

    // 使用填充模式PKCS #7
    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
    stfEncryptor.Put(reinterpret_cast<const unsigned char *>(plaintext.c_str()), plaintext.length() + 1);
    stfEncryptor.MessageEnd();

    return ciphertext;
}

std::string AESTool::AES_decrypt(const std::string &ciphertext, const std::string &key) {
    std::string decryptedtext;

    // AES解密
    CryptoPP::AES::Decryption aesDecryption((unsigned char *) key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (unsigned char *) key.c_str());

    // 使用填充模式PKCS #7
    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
    stfDecryptor.Put(reinterpret_cast<const unsigned char *>(ciphertext.c_str()), ciphertext.size());
    stfDecryptor.MessageEnd();

    return decryptedtext;
}


