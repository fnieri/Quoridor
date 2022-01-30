#pragma once


#include <string>

class PasswordEncrypter {
    private:
        std::string passwordToEncrypt;
        std::string finalPassword;
        int saltKey;
    public:
        
        //Encrypter hashes given password
        PasswordEncrypter(std::string passwordToEncrypt);
        
        //Hashing algorithm can use SHA1, SHA2, SHA3, SHA256
        std::string hashingAlgorithm(std::string);
        
        //Generates random salt key to use to encrypt password
        int saltKeyGenerator();
};
