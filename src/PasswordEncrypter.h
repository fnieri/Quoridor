#pragma once


#include <string>

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
        std::string createDigest(std::string saltedPassword);
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

        //Setters
        void setSaltKey(std::string newSaltKey);
};
