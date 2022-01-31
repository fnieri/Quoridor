#pragma once


#include "include/cryptopp/cryptlib.h"
#include "include/cryptopp/sha.h"
#include "include/cryptopp/osrng.h"
#include "include/cryptopp/pwdbased.h"
#include "include/cryptopp/hex.h"

#include <chrono>
#include <string>

#include <iostream>

class PasswordEncrypter {
    private:
        std::string passwordToEncrypt;
        std::string saltKey;
        /**
         * @brief Generate saltKey given Unix epoch time
         * 
         */
        void generateSaltKey();
        /**
         * @brief Hash password given a saltkey
         * 
         */
        std::string createDigest();
    public:
        
        //Encrypter hashes given password
        //Constructor for encrypting
        PasswordEncrypter(std::string passwordToEncrypt);
        
        //Constructor for decrypting given a salt key and a password to encrypt
        PasswordEncrypter(std::string passwordToEncrypt, std::string saltKey);
        
        //Hash saltKey + password
        std::string hashPassword();
        
        //Getters
        std::string getSaltKey();

};
