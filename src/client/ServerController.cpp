#include "ServerController.h"

using json = nlohmann::json;

ServerController::ServerController(std::shared_ptr<ViewController> viewController) :
    viewController{viewController}
{
}

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

void ServerController::isGameOver(bool over)
{
    viewController->isGameOver(over);
}

/* Game handler */
void ServerController::movePlayer(std::string action)
{
    json playerAction = json::parse(action); // String to json

    int x {playerAction["move"]["end_position"]["x"]};
    int y {playerAction["move"]["end_position"]["y"]};
    Point end_position {x, y};
    PawnColors playerColor = (PawnColors)playerAction["player_id"]; // Spot playerID

    std::shared_ptr<PlayerAction> action {board, dictPlayer[playerColor], end_position / 2}; 

    if (action->executeAction() && !action->isGameOver())
        currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers; // change turns if the PlayerAction is valid, idk if we need to do this here

    else if (action->isGameOver())
        isGameOver(true);
}

void ServerController::placeWall(std::string action)
{
    json wallAction = json::parse(action); // String to json

    int x {wallAction["move"]["wall_cell"]["x"]};
    int y {wallAction["move"]["wall_cell"]["y"]};
    WallOrientation wallOrientation = wallAction["move"]["wall_orientation"].jsonToOrientation;
    Point wallCell {x, y};
    PawnColors playerColor = (PawnColors)wallAction["player_id"]; // Spot playerID

    std::shared_ptr<WallAction> action {board, dictPlayer[playerColor], end_position / 2, wallOrientation};

    if (action->executeAction() && !action->isGameOver())
        currentPlayerIndex = (currentPlayerIndex + 1) % nPlayers;

    else if (action->isGameOver())
        isGameOver(true);
}

// TODO getReceivers() // we need this to send messages to all gamers in the group chat
// need the server to send this

/* Chat handler */
// Two types of messages : those sent in DM and those sent to a game party

// when we receive a message from the View, we send it to the Server
void ServerController::sendDirectMessage(std::string sender, std::string receiver, std::string msg)
{
    json msg = SerializableMessageFactory::serializeFriendMessage(sender, receiver, msg);   // make a json formated message
    send(msg);
}

void ServerController::sendGroupMessage(std::string sender, std::string msg, int gameId)
{
    // TODO get all receivers
    json msg = SerializableMessageFactory::serializeInGameMessage(sender, receivers, message, gameID);
    send(msg);
}

// when we receive a message from the Server, we send it to the View to show it to others
void ServerController::receiveGroupMessage(std::string msg)
{
    viewController->receiveGroupMessage(json::parse(msg));
    //return json::parse(msg);    
}

void ServerController::receiveDirectMessage(std::string msg)
{
    viewController->receiveDirectMessage(json::parse(msg));
}

// Servers sends us all the messages to load them to the players' View
// Do we load the messages one at a time or all the messages together
void ServerController::loadDirectMessages(std::string username)
{
    // message format not up to date yet in SerializableMessageFactory
    // json msg = SerializableMessageFactory::serializeUserChatBoxRequest(ChatInteraction::SERVER_RELAY_MESSAGE, ?);
    // why send the message ? and timestamp ? and ChatBoxId ??
    // send(msg);
}

void ServerController::loadGroupMessages(std::string msg)
{
    // json msg = SerializableMessageFactory::serializeUserChatBoxRequest(ChatInteraction::SERVER_RELAY_MESSAGE, ?);
    // send(msg);}

/* Network handler */
void ServerController::sendFriendRequest(std::string receiver)
{
    // FriendAction friend_action = ... ? what is that ?

    // json msg = SerializableMessageFactory::serializeFriendRequest(friend_action, sender, receivers);
    // send(msg);
}

void ServerController::checkLeaderBoard()
{
    // how to access leaderboard ? send a pointer to it ?
}

void ServerController::sendInvite(std::string aFriend, std::string gameSetup)
{
    // json msg = SerializableMessageFactory::serializeGameRequest(GameAction gameAction ?, afriend); // not implemented yet
    // send(msg);
}

void ServerController::joinGame(int gameId)
{
    // json msg = SerializableMessageFactory::serializeQueueJoinRequest(friend_action, sender, receivers); // not implemented yet
    // send(msg);
}

void ServerController::askPause(std::string aFriend)
{
    // json msg = SerializableMessageFactory::serializeInGameRequest(GameAction::ASK_PAUSE, username);
    // send(msg);
}

void ServerController::registerPlayer(std::string username, std::string password)
{
    // json msg = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::REGISTER,username, password);
    // send(msg);
}

void ServerController::logIn(std::string username, std::string password)
{
    // json msg = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN,username, password);
    // send(msg);
}

void ServerController::logOut()
{
    // need to add log out to enum class of ClientAuthAction
    // json msg = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGOUT,username, password);
    // send(msg);
}

void ServerController::saveGame(std::string username)
{
    // json msg = SerializableMessageFactory::serializeInGameRequest(GameAction::PROPOSE_SAVE, username);
    // send(msg);
}

void ServerController::pauseGame(std::string username)
{
    // json msg = SerializableMessageFactory::serializeInGameRequest(GameAction::ASK_PAUSE, username);
    // send(msg);
}
