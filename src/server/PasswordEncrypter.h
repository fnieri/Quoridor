/**

 * @brief Password Encrypter using cryptopp::SHA256 to encrypt passwords
 * upon registering or logging in
 * @details The encrypter uses a salt key defined by the epoch time of the call
 * the Encrypter which will be hashed is a combination of the salt key and the
 * password. The final digest will be the SHA256 digest, which will either brief
 * used to verify if the login was successful and to append an user with his password
 * and saltKey to the database. PasswordEncrypter is a singleton so it needs to be instanciated only once
 */

#pragma once

#include <memory>
#include <string>
#include <vector>

class PasswordEncrypter
{
private:
   /**
    * @brief Generate saltKey given Unix epoch time
    *  @return std::string saltKey
    */
   static std::string generateSaltKey();
   /**
    * @brief Hash password given a saltedPassword
    * @param saltedPassword saltKey + vanilla password
    *
    */
   static std::string createDigest(std::string saltedPassword);

   PasswordEncrypter();

public:
   static std::unique_ptr<PasswordEncrypter> &Instance()
   {
       static std::unique_ptr<PasswordEncrypter> singleton;
       if (!singleton)
           singleton = std::move(std::unique_ptr<PasswordEncrypter> {new PasswordEncrypter});
       return singleton;
   }

   /**
    * @brief Hash password given upon registering as salt key + password with SHA256, return salt key an to Database
    * @see SHA256
    * @see Salt key
    * @see One-way encryption
    * @param std::string passwordToEncrypt password input by user
    * @param std::string username
    * @return string Salt key and hash to store in database
    * first parameter in vector is saltKey, second is the hash
    */
   static std::vector<std::string> registerEncryption(std::string passwordToEncrypt);
   /**
    * @brief Compare login password with saltKey and hash found in database
    * @param passwordToEncrypt password input by user
    * @param saltKey saltKey used upon registering, found in database
    * @param databaseHash hash calculated upon registering, found in database
    * @return bool check if saltedPassword hash matches hash in database
    */
   static bool compareHash(std::string passwordToEncrypt, std::string saltKey, std::string databaseHash);
};
