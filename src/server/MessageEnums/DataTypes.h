/**
 * @author Francesco Nieri
 * @brief Enums for data type transmission
 * @date 21/02/2022
*/

#pragma once 

enum class DataType {
  GAME_ACTION,
  LEADERBOARD,
  FRIENDS_LIST,
  GAME_CONFIG,  
}

inline const char *toJsonOutput(DataType d) 
{
    switch (d) {
      case DataType::GAME_ACTION:
          return "game_action";
      case DataType::LEADERBOARD:
          return "leaderboard";
      case DataType::FRIENDS_LIST:
          return "friends_list";
      case DataType::GAME_CONFIG:
          return "game_config";
    }
    return "";
}
