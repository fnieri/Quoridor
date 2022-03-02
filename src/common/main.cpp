#include "GameSetupSerializableMessageFactory.h"
#include "SerializableMessageFactory.h"
#include "iostream"

using json = nlohmann::json;

int main()
{
    std::vector<std::string> b = {"a", "b", "c"};
    json a = SerializableMessageFactory::serializeGameSetup(GameMode::FOG_OF_WAR, GameInvite::GAME_ACCEPT_INVITE, b, 1, 2);
    std::cout << a.dump(4) << std::endl;
}
