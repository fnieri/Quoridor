#include "PasswordEncrypter.h"
#include <iostream>
int main() {
    PasswordEncrypter a("password123", "1234567890");
    std::cout << a.hashPassword() << std::endl;
    return 0;
}