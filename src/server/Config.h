/**
 * @file config.h
 * @author Sacha Testaert
 * @brief Creates maps of client and server config
 * @date 2022-03-18
 */

#pragma once

#include "ConfigEnums.h"

#include <fstream> // to open and read in a given file
#include <iostream>
#include <map>
#include <map>
#include <memory>

class ConfigHandler
{
public:
    /**
     * @brief Return a client property from config file
     * @param ClientProperty Requested client config
     * @return std::string Requested property
     */
    auto getClientProperty(ClientProperty) -> std::string;
    /**
     * @brief Return a server property from config file
     * @param ServerProperty Requested server property
     * @return std::string Requsted server property
     */
    auto getServerProperty(ServerProperty) -> std::string;

    static std::unique_ptr<ConfigHandler> &Instance()
    {
        static std::unique_ptr<ConfigHandler> singleton;
        if (!singleton) {
            singleton = std::move(std::make_unique<ConfigHandler> ());
        }
        return singleton;
    }
private:

    ConfigHandler();
    /**
     * @brief Get the Map object of a config file
     *
     * @param filename
     * @return map<string,  string>
     */
    static auto getMapFromConfigFile(const std::string &filename) -> std::map<std::string, std::string>;

    /**
     * @brief Get the Key Value object
     * @details Gets the key value from separating each side of a line from an equal symbal "=";
     * Is called within the getMapFromConfigFile(string) method]
     * @param line
     * @return pair<string, string>
     */
    static auto getKeyValue(const std::string &line) -> std::pair<std::string, std::string>;

    /**
     * @brief Get the Server Config map
     *
     * @return map< string,  string>
     */
    auto getServerConfig() -> std::map<std::string, std::string>;

    /**
     * @brief Get the Client Config map
     *
     * @return map< string, string>
     */
    auto getClientConfig() -> std::map<std::string, std::string>;

};