#include <catch2/catch2.hpp>

#include "src/server/PasswordEncrypter.h"

#include <cstdlib>
#include <unistd.h>

SCENARIO("Encrypting upon registering")
{
    GIVEN("An encrypter that generates two passwords 1 second apart")
    {
        std::unique_ptr<PasswordEncrypter> anEncrypter = PasswordEncrypter::Instance();
        
        std::vector<std::string> firstRegisterHash = anEncrypter->registerEncrypt("password123");
        sleep(1);
        std::vector<std::string> secondRegisterHash = anEncrypter->registerEncrypt("password123");
        
        THEN("Salt keys and digests should be different")
        {
            REQUIRE_FALSE(firstRegisterHash[0], secondRegisterHash[0]);
            REQUIRE_FALSE(firstRegisterHash[1], secondRegisterHash[1]);
        }
    }
    GIVEN("Two hashes generated in the same second")
    {
        THEN("Salt Keys and hashes should be the same")
        {
            REQUIRE(anEncrypter.registerEncrypt("password123") == anEncrypter("password123"));
        }
    }
}

SCENARIO("Encrypting upon login")
{
    GIVEN("SaltKey + passwordEncrypt with known digest")
    {
        std::unique_ptr<PasswordEncrypter> anEncrypter = PasswordEncrypter::Instance();
        
        THEN("Hashing should return true")
        {
          REQUIRE(anEncrypter.compareHash("password123", "1234567890", "F6211D8C3930C89E962D5B293541D3113D95F9CED1DF14CA96517B98F03B31D9") == true)
        }
        THEN("By changing salt key, digest should be the same")
        {
          REQUIRE(anEncrypter.compareHash("password123", "1234567891", "F6211D8C3930C89E962D5B293541D3113D95F9CED1DF14CA96517B98F03B31D9") == false);
        }
    }
}
