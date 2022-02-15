#include <catch2/catch.hpp>

#include "src/server/PasswordEncrypter.h"
#include <cstdlib>
#include <unistd.h>

SCENARIO("Encrypting with no default saltKey")
{
    GIVEN("Two encrypters that generate their own salt keys 1 second apart")
    {

        PasswordEncrypter firstEncrypterNoSalt("password123");
        sleep(1);
        PasswordEncrypter secondEncrypterNoSalt("password123");
        THEN("Salt keys must be different as they are generated in different seconds")
        {
            REQUIRE_FALSE(firstEncrypterNoSalt.getSaltKey() == secondEncrypterNoSalt.getSaltKey());
            REQUIRE_FALSE(firstEncrypterNoSalt.hashPassword() == secondEncrypterNoSalt.hashPassword());
        }
        WHEN("Salt keys are set to be the same")
        {
            firstEncrypterNoSalt.setSaltKey("1234567890");
            secondEncrypterNoSalt.setSaltKey("1234567890");
            THEN("Digest should be the same")
            {
                REQUIRE(firstEncrypterNoSalt.hashPassword() == secondEncrypterNoSalt.hashPassword());
            }
        }
    }
}

SCENARIO("Encrypting with a default saltKey")
{
    GIVEN("An encrypter with known salt key and password")
    {
        PasswordEncrypter knownEncrypter("password123", "1234567890");
        THEN("Digest should be F6211D8C3930C89E962D5B293541D3113D95F9CED1DF14CA96517B98F03B31D9")
        {
            REQUIRE(knownEncrypter.hashPassword() == "F6211D8C3930C89E962D5B293541D3113D95F9CED1DF14CA96517B98F03B31D9");
        }
        THEN("By changing the salt key, digest should change")
        {
            knownEncrypter.setSaltKey("1234567891");
            REQUIRE_FALSE(knownEncrypter.hashPassword() == "F6211D8C3930C89E962D5B293541D3113D95F9CED1DF14CA96517B98F03B31D9");
        }
    }
}
