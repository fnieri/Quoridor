// Written by Francesco Nieri

#include "PasswordEncrypter.h"

#include <cryptlib.h>
#include <hex.h>
#include <osrng.h>
#include <pwdbased.h>
#include <sha.h>

#include <chrono>

PasswordEncrypter::PasswordEncrypter()
{
}

std::string PasswordEncrypter::generateSaltKey()
{
    // https://stackoverflow.com/questions/6012663/get-unix-timestamp-with-c
    // Salt key is unix time stamp as it is unique EVERY NEW SECOND
    // https://stackoverflow.com/questions/36955261/accepted-method-to-generate-salt-for-a-password-hash-function-c

    int64_t timestamp {std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()};
    std::string saltKey {std::to_string(timestamp)};
    return saltKey;
}

std::string PasswordEncrypter::createDigest(std::string saltedPassword)
{
    std::string output;

    // http://www.cplusplus.com/forum/beginner/60604/
    // Thanks to Texan40 for help on how to hash a password

    // IMPORTANT NOTE: This should be CryptoPP::byte but it doesn't compile for me (If you see unsigned char in any emcrypting file IT IS CRYPTOPP::BYTE!!!)

    unsigned char digest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256 hashAlgorithm; // Using SHA256 as encryption algorithm

    hashAlgorithm.CalculateDigest(digest, (const unsigned char *)saltedPassword.c_str(), saltedPassword.size());

    CryptoPP::HexEncoder encoder;
    CryptoPP::StringSink *stringSink = new CryptoPP::StringSink(output);
    // This method is described in the cryptopp wiki
    // Attach stringSink to Encoder to decode byte digest output
    encoder.Attach(stringSink);
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    // Crypto++ handles deletion of stringSink in smartptr.h, so no need for deletion
    // Smart pointers don't work as they will get deleted twice, but cryptlib uses
    // Their own smart pointers

    return output;
}

bool PasswordEncrypter::compareHash(std::string passwordToEncrypt, std::string saltKey, std::string databaseHash)
{
    std::string saltedPassword = saltKey + passwordToEncrypt;

    if (Instance()->createDigest(saltedPassword) == databaseHash)
        return true;
    return false;
}

std::vector<std::string> PasswordEncrypter::registerEncryption(std::string passwordToEncrypt)
{

    std::string saltKey = Instance()->generateSaltKey();
    std::string saltedPassword = saltKey + passwordToEncrypt;
    std::string hashedPassword = Instance()->createDigest(saltedPassword);

    std::vector<std::string> returnVector = {saltKey, hashedPassword};
    return returnVector;
}
