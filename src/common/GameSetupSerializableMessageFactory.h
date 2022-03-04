#pragma once

#include "MessageEnums/Actions/GameActions.h"
#include "MessageEnums/Modes/GameModes.h"
#include <nlohmann/json.hpp>

class GameSetupSerializableMessageFactory
{
public:
    /**
     * @brief serialize a game setup
     * @param gameMode current game mode (unused (guess why!))
     * @param players list of players that are playing a game
     * @return json of setup as such
     * {
     * {"action", "create_game"},
     * {"domain", "game_setup"},
     * {"game_mode", "fow"},
     * {"players", ["car", "mine", "bur", "ana]}
     * }
     */
    static nlohmann::json serializeGameSetup(GameMode gameMode, std::vector<std::string> &players);
    /**
     * @brief serialize a request to participate in a game
     * @param gameSetup join/quit
     * @param gameID id of game
     * @return json of setup as such
     * {
     * {"action", join|quit},
     * {"domain", "game_setup"},
     * {"game_id", game_id},
     * }
     */
    static nlohmann::json serializeGameParticipationRequest(GameSetup gameSetup, int gameID);
    /**
     * @brief Serialize a request to create a game
     * @param sender Creator (Boris)
     * @param receivers ["Cmake", "cmongo-cxx", "3.16"]
     * @param configuration serialized json of board
     * @return json of creation as such
     * {
     * {"action", "create_game"},
     * {"domain", "game_setup"},
     * {"sender", "Cookie"},
     * {"receivers", ["P1", "P2", "P3"]},
     * {"configuration", **json of board**}
     * }
     */
    static nlohmann::json serializeGameCreationRequest(const std::string &sender, std::vector<std::string> &receivers, nlohmann::json configuration);

};
