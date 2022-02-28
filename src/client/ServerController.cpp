#include "ServerController.h"
#include "Controller.h"
#include "Board.h"
#include "BoardComponent.h"
#include "Player.h"
#include "PlayerAction.h"
#include "PlayerEnum.h"
#include "Point.h"
#include "WallAction.h"
#include "WallEnum.h"
// #include "../server/SerializableMessageFactory.h"

#include <memory>
#include <vector>

using json = nlohmann::json;

class Player;

ServerController::ServerController()
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

void ServerController::setDict(std::map<PawnColors, std::shared_ptr<Player>> dict_player)
{
    dictPlayer = dict_player;
}

bool ServerController::isGameOver(bool over)
{
    return over;
}

/* Game handler */
void ServerController::movePlayer(std::string action)
{
    json playerAction = json::parse(action); // String to json

    int x {playerAction["move"]["end_position"]["x"]};
    int y {playerAction["move"]["end_position"]["y"]};
    Point end_position {x, y};
    PawnColors playerColor = (PawnColors)playerAction["player_id"]; // Spot playerID
    std::shared_ptr<Player> player = dictPlayer[playerColor];
    std::shared_ptr<PlayerAction> playersAction = std::make_shared<PlayerAction>(board, player, end_position / 2);
    playersAction->executeAction();
    if (playersAction->isGameOver())
        isGameOver(true);
}

void ServerController::placeWall(std::string action)
{
    json wallAction = json::parse(action); // String to json

    int x {wallAction["move"]["wall_cell"]["x"]};
    int y {wallAction["move"]["wall_cell"]["y"]};
    // WallOrientation wallOrientation = wallAction["move"]["wall_orientation"].jsonToOrientation;
    // Point wallCell {x, y};
    // PawnColors playerColor = (PawnColors)wallAction["player_id"]; // Spot playerID

    // td::shared_ptr<WallAction> wallAction {board, dictPlayer[playerColor], end_position / 2, wallOrientation};

    // wallAction->executeAction();
    // if (wallAction->isGameOver()) isGameOver(true);
}

// TODO getReceivers() // we need this to send messages to all gamers in the group chat
// need the server to send this

/* Chat handler */
// Two types of messages : those sent in DM and those sent to a game party

// when we receive a message from the View, we send it to the Server
void ServerController::sendDirectMessage(std::string sender, std::string receiver, std::string msg)
{
    // json to_send = SerializableMessageFactory::serializeFriendMessage(sender, receiver, msg);   // make a json formated message
    // send(to_send);
}

void ServerController::sendGroupMessage(std::string sender, std::string msg, int gameId)
{
    // TODO get all receivers
    // json to_send = SerializableMessageFactory::serializeInGameMessage(sender, receivers, message, gameID);
    // send(to_send);
}

bool ServerController::isDirectMessageReceived(bool received)
{
    return received;
}

bool ServerController::isGroupMessageReceived(bool received)
{
    return received;
}

// when we receive a message from the Server, we send it to the View to show it to others
json ServerController::receiveGroupMessage(std::string msg)
{
    isGroupMessageReceived(true);
    return json::parse(msg);
}

json ServerController::receiveDirectMessage(std::string msg)
{
    isDirectMessageReceived(true);
    return json::parse(msg);
}

// Servers sends us all the messages to load them to the players' View
// Do we load the messages one at a time or all the messages together
void ServerController::loadDirectMessages(std::string username)
{
    // message format not up to date yet in SerializableMessageFactory
    // json to_send = SerializableMessageFactory::serializeUserChatBoxRequest(ChatInteraction::SERVER_RELAY_MESSAGE, ?);
    // why send the message ? and timestamp ? and ChatBoxId ??
    // send(to_send);
}

void ServerController::loadGroupMessages(int gameId)
{
    // json to_send = SerializableMessageFactory::serializeUserChatBoxRequest(ChatInteraction::SERVER_RELAY_MESSAGE, ?);
    // send(to_send);
}

/* Network handler */
void ServerController::sendFriendRequest(std::string receiver)
{
    // FriendAction friend_action = ... ? what is that ?

    // json to_send = SerializableMessageFactory::serializeFriendRequest(friend_action, sender, receivers);
    // send(to_send);
}

void ServerController::checkLeaderBoard()
{
    // how to access leaderboard ? send a pointer to it ?
}

void ServerController::sendInvite(std::string aFriend, std::string gameSetup)
{
    // json to_send = SerializableMessageFactory::serializeGameRequest(GameAction gameAction ?, afriend); // not implemented yet
    // send(to_send);
}

void ServerController::joinGame(int gameId)
{
    // json to_send = SerializableMessageFactory::serializeQueueJoinRequest(friend_action, sender, receivers); // not implemented yet
    // send(to_send);
}

void ServerController::askToPause(std::string aFriend)
{
    // json to_send = SerializableMessageFactory::serializeInGameRequest(GameAction::ASK_PAUSE, username);
    // send(to_send);
}

void ServerController::registerPlayer(std::string username, std::string password)
{
    // json to_send = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::REGISTER,username, password);
    // send(to_send);
}

void ServerController::logIn(std::string username, std::string password)
{
    // json to_send = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN,username, password);
    // send(to_send);
}

void ServerController::logOut()
{
    // need to add log out to enum class of ClientAuthAction
    // json to_send = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGOUT,username, password);
    // send(to_send);
}

void ServerController::saveGame(std::string username)
{
    // json to_send = SerializableMessageFactory::serializeInGameRequest(GameAction::PROPOSE_SAVE, username);
    // send(to_send);
}

void ServerController::pauseGame(std::string username)
{
    // json to_send = SerializableMessageFactory::serializeInGameRequest(GameAction::ASK_PAUSE, username);
    // send(to_send);
}
