#ifndef __PASSWORDENCRYPTER_H
#define __PASSWORDENCRYPTER_H

#include <string>

class PasswordEncrypter {
    private:
        std::string passwordToEncrypt;
        std::string finalPassword;
    public:
        PasswordEncrypter(std::string passwordToEncrypt);
        std::string hashingAlgorithm(std::string);
};
#endif