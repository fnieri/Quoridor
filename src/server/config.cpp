/**
 * @file config.h
 * @author Sacha Testaert
 * @brief Creates maps of user and server config
 * @date 2022-03-18
 */

#include "config.h"

std::pair< std::string,  std::string> ConfigHandler::getKeyValue(std::string line){
    auto equal_index = line.std::string::find("=");
    std::string key = line.std::string::substr(0, equal_index);
    std::string value = line.std::string::substr(equal_index + 1);
    return  std::make_pair(key, value);
}

std::map<std::string, std::string> ConfigHandler::getMapFromConfigFile(std::string config_file){
    std::ifstream file (config_file);
    std::string line;
    std::pair<std::string,std::string> tup;
    std::map<std::string,  std::string> extractedValues;
    if (file.std::ifstream::is_open()){

    while(std::getline(file, line)){
        tup = getKeyValue(line);
        extractedValues.insert(tup);
    }
    file.close();
    }

    return extractedValues;
}

std::map<std::string, std::string> ConfigHandler::getServerConfig(){
        return getMapFromConfigFile("server_config.txt");
    };

std::map<std::string, std::string> ConfigHandler::getUserConfig(){
    return getMapFromConfigFile("client_config.txt");
};


// int main() {

//     std::map< std::string,  std::string> user_config = ConfigHandler::getUserConfig();
//     std::map< std::string,  std::string> server_config = ConfigHandler::getServerConfig();

//     auto iter = user_config.begin();
//     std::cout << "Contenu du dictionnaire extrait du fichier user_config.txt: " <<std::endl;
//     std::cout << std::endl;
//     while (iter != user_config.end()) {
//         std::cout <<  iter->first << " = "
//                     << iter->second << "\n";
//         ++iter;
//     }

//     std::cout << std::endl;

//     auto p = server_config.begin();
//     std::cout << "Contenu du dictionnaire extrait du fichier user_config.txt: " <<std::endl;
//     std::cout << std::endl;
//     while (p != server_config.end()) {
//         std::cout <<  p->first << " = "
//                     << p->second << "\n";
//         ++p;
//     }

//     std::cout << std::endl;

//     return 0;
// }