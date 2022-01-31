#include "PasswordEncrypter.h"

PasswordEncrypter::PasswordEncrypter(std::string passwordToEncrypt) : 
    passwordToEncrypt{passwordToEncrypt} {generateSaltKey();}

PasswordEncrypter::PasswordEncrypter(std::string passwordToEncrypt, std::string saltKey) :
    passwordToEncrypt{passwordToEncrypt}, saltKey{saltKey} {}

void PasswordEncrypter::generateSaltKey() {
    //https://stackoverflow.com/questions/6012663/get-unix-timestamp-with-c
    //Salt key is unix time stamp as it is unique
    //https://stackoverflow.com/questions/36955261/accepted-method-to-generate-salt-for-a-password-hash-function-c
    
    int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
    saltKey = std::to_string(timestamp);
}

std::string PasswordEncrypter::createDigest() {
    std::string output;

    //http://www.cplusplus.com/forum/beginner/60604/ 
    //Thanks to Texan40 for help on how to hash a password
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256 hash;
    
    hash.CalculateDigest(digest, (const CryptoPP::byte *)saltKey.c_str(), saltKey.size());

    CryptoPP::HexEncoder encoder;
    CryptoPP::StringSink *stringSink = new CryptoPP::StringSink(output);
    
    encoder.Attach(stringSink);
    encoder.Put(digest,sizeof(digest));
    encoder.MessageEnd();

    //Crypto++ handles deletion of stringSink in smartptr.h, so no need for deletion
    //Smart pointers don't work as they will get deleted twice, but cryptlib uses
    //Their own smart pointers
    
    return output;
}

std::string PasswordEncrypter::hashPassword() {
    passwordToEncrypt = saltKey + passwordToEncrypt;
    return createDigest();
}

std::string PasswordEncrypter::getSaltKey() {
    return saltKey;
}