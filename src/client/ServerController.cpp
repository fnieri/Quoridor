#include "ServerController.h"

using json = nlohmann::json;

ServerController::ServerController()
{
}

/* Game handler */

void ServerController::setBoard(std::shared_ptr<Board> theBoard) 
{
    board = theBoard;
}

void ServerController::setPlayers(std::vector<std::shared_ptr<Player>> thePlayers)
{
    players = thePlayers;
}

void ServerController::setDict(map<PawnColors, shared_ptr<Player>> dict_player)
{
    dictPlayer = dict_player;
}

void ServerController::movePlayer(std::string action)
{
    json playerAction = json::parse(action);    // String to json 

    int x{playerAction["move"]["end_position"]["x"]};  
    int y{playerAction["move"]["end_position"]["y"]};
    Point end_position{x,y};
    PawnColors playerColor = (PawnColors) playerAction["player_id"]; // Repere playerID
    
    std::shared_ptr<PlayerAction> action {board, dictPlayer[playerColor], end_position / 2};   // i need the Player and the Point of the move
    
    if (action->executeAction() && !action->isGameOver())
        currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers; // change turns if the PlayerAction is valid
    
    else if (action->isGameOver()) isGameOver(true);
}

void ServerController::placeWall(std::string action)
{
    json wallAction = json::parse(action);    // String to json 

    int x{wallAction["move"]["wall_cell"]["x"]};  
    int y{wallAction["move"]["wall_cell"]["y"]};
    WallOrientation wallOrientation = wallAction["move"]["wall_orientation"].jsonToOrientation;
    Point wallCell{x,y};
    PawnColors playerColor = (PawnColors) wallAction["player_id"]; // Repere playerID
    
    std::shared_ptr<WallAction> action {board, dictPlayer[playerColor], end_position / 2, wallOrientation};   // i need the Player and the Point of the move
    
    if (action->executeAction() && !action->isGameOver())
        currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers; // change turns if the PlayerAction is valid
    
    else if (action->isGameOver()) isGameOver(true);
}

// TODO getReceivers() // we need this to send messages to all gamers in the group chat


/* Chat handler */
// Two types of messages : those sent in DM and those sent to a game party

// recoit msg de la Vue envoie au sercver
void ServerController::sendDirectMessage(std::string sender, std::string receiver, std::string msg)
{
    json SerializableMessageFactory::serializeFriendMessage(sedner, receiver, message);
    
    send(msg);
}

void ServerController::sendGroupMessage(std::string sender, std::vector<std::string> receiver, std::string msg, int gameId)
{
    // TODO get all receivers
    json SerializableMessageFactory::serializeInGameMessage(sender, receivers, message, gameID);
    
    send(msg);
}

// msg recu du server quon envoie a la vue
json ServerController::receiveGroupMessage(std::string msg)
{
    return json::parse(msg);
}

void ServerController::receiveDirectMessage(std::string receiver, std::string msg, int gameId)
{
}

void ServerController::loadMessages(std::string receiver)
{
}

void ServerController::loadMessages(int gameId)
{
}

/* Network handler */
void ServerController::sendFriendRequest(std::string receiver)
{
}

void ServerController::checkLeaderBoard()
{
}

void ServerController::sendInvite(std::string aFriend, std::string gameSetup)
{
}

void ServerController::joinGame(int gameId)
{
}

void ServerController::askPause(std::string aFriend)
{
}

void ServerController::registerPlayer(std::string username, std::string password)
{
}

void ServerController::logIn(std::string username, std::string password)
{
}

void ServerController::logOut()
{
}

void ServerController::saveGame()
{
}

void ServerController::pauseGame()
{
}
