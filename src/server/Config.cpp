/**
 * @file config.h
 * @author Sacha Testaert
 * @brief Creates maps of client and server config
 * @date 2022-03-18
 */

#include "Config.h"

ConfigHandler::ConfigHandler()
{
}

auto ConfigHandler::getKeyValue(const std::string &line) -> std::pair<std::string, std::string>
{
    auto equal_index = line.std::string::find('=');
    std::string key = line.std::string::substr(0, equal_index);
    std::string value = line.std::string::substr(equal_index + 1);
    return std::make_pair(key, value);
}

auto ConfigHandler::getMapFromConfigFile(const std::string &config_file) ->
std::map<std::string, std::string>
{
    std::ifstream file(config_file);
    std::string line;
    std::pair<std::string, std::string> tup;
    std::map<std::string, std::string> extractedValues;
    if (file.std::ifstream::is_open()) {
        while (std::getline(file, line)) {
            tup = Instance()->getKeyValue(line);
            extractedValues.insert(tup);
        }
        file.close();
    }
    return extractedValues;
}

auto ConfigHandler::getServerConfig() ->
std::map<std::string, std::string>
{
    return Instance()->getMapFromConfigFile("src/server/server_config.txt");
};

auto ConfigHandler::getClientConfig() -> std::map<std::string, std::string>
{
    return Instance()->getMapFromConfigFile("src/server/client_config.txt");
};

auto ConfigHandler::getClientProperty(ClientProperty c) -> std::string
{
    return Instance()->getClientConfig()[toConfigString(c)];
}

auto ConfigHandler::getServerProperty(ServerProperty s) -> std::string
{
    return Instance()->getServerConfig()[toConfigString(s)];
}