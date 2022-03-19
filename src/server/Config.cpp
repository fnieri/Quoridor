/**
 * @file config.h
 * @author Sacha Testaert
 * @brief Creates maps of user and server config
 * @date 2022-03-18
 */

#include "Config.h"

ConfigHandler::ConfigHandler() {}

std::pair< std::string,  std::string> ConfigHandler::getKeyValue(const std::string& line){
    auto equal_index = line.std::string::find('=');
    std::string key = line.std::string::substr(0, equal_index);
    std::string value = line.std::string::substr(equal_index + 1);
    return  std::make_pair(key, value);
}

std::map<std::string, std::string> ConfigHandler::getMapFromConfigFile(const std::string& config_file){
    std::ifstream file (config_file);
    std::string line;
    std::pair<std::string, std::string> tup;
    std::map<std::string, std::string> extractedValues;
    if (file.std::ifstream::is_open()){

        while(std::getline(file, line)){
            tup = Instance()->getKeyValue(line);
            extractedValues.insert(tup);
        }
        file.close();
    }

    return extractedValues;
}

std::map<std::string, std::string> ConfigHandler::getServerConfig(){
    return Instance()->getMapFromConfigFile("server_config.txt");
};

std::map<std::string, std::string> ConfigHandler::getUserConfig(){
    return Instance()->getMapFromConfigFile("user_config.txt");
};
