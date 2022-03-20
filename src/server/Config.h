/**
 * @file config.h
 * @author Sacha Testaert
 * @brief Creates maps of client and server config
 * @date 2022-03-18
 */

#include <fstream> // to open and read in a given file
#include <iostream>
#include <map>
#include <map>
#include <memory>

class ConfigHandler
{
public:
    /**
     * @brief Get the Server Config map
     *
     * @return map< string,  string>
     */
    static std::map<std::string, std::string> getServerConfig();

    /**
     * @brief Get the Client Config map
     *
     * @return map< string, string>
     */
    static std::map<std::string, std::string> getClientConfig();
    ConfigHandler();

private:
    static std::unique_ptr<ConfigHandler> &Instance()
    {
        static std::unique_ptr<ConfigHandler> singleton;
        if (!singleton)
            singleton = std::move(std::unique_ptr<ConfigHandler> {new ConfigHandler});
        return singleton;
    }
    /**
     * @brief Get the Map object of a config file
     *
     * @param filename
     * @return map<string,  string>
     */
    static std::map<std::string, std::string> getMapFromConfigFile(const std::string &filename);

    /**
     * @brief Get the Key Value object
     * @details Gets the key value from separating each side of a line from an equal symbal "=";
     * Is called within the getMapFromConfigFile(string) method]
     * @param line
     * @return pair<string, string>
     */
    static std::pair<std::string, std::string> getKeyValue(const std::string &line);
};