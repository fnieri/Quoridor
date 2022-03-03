#include "ServerController.h"
#include "Controller.h"
#include "Board.h"
#include "BoardComponent.h"
#include "Player.h"
#include "PlayerAction.h"
#include "PlayerEnum.h"
#include "../common/Point.h"
#include "WallAction.h"
#include "WallEnum.h"
#include "../common/SerializableMessageFactory.h"
#include "ServerBridge.h"

#include <memory>
#include <vector>

using json = nlohmann::json;

class Player;

ServerController::ServerController()
{
    serverBridge {"localhost", 12345, this};  
    serverBridge.startHandling();
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

bool ServerController::isDirectMessageReceived(bool received)
{
    return received;
}

bool ServerController::isGroupMessageReceived(bool received)
{
    return received;
}

/* GENERAL REQUEST SENDER */

void ServerController::sendDirectMessage(std::string sender, std::string receiver, std::string msg)
{
    json to_send = SerializableMessageFactory::serializeFriendMessage(sender, receiver, msg);   // make a json formated message
    serverBridge.send(to_send);
}

void ServerController::sendGroupMessage(std::string sender, std::string msg, int gameId)
{
    // find all receivers ?
    json to_send = SerializableMessageFactory::serializeInGameMessage(sender, receivers, msg, gameID);
    serverBridge.send(to_send);
}

// send DM chat request
void ServerController::loadDirectMessages(std::string sender, std::string receiver)
{
    json to_send = ObjectExchangesSerializableMessageFactory::serializeFriendChatRequest(sender, receiver);
    serverBridge.send(to_send);
}


void ServerController::sendFriendRequest(std::string receiver)
{
    json to_send = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, sender, receivers);
    serverBridge.send(to_send);
}

// send leaderboard ressource request
void ServerController::checkLeaderBoard()
{
    json to_send = SerializableMessageFactory::serializeRequestExchange(DataType::LEADERBOARD);
    serverBridge.send(to_send);
}

void ServerController::sendInvite(std::string friend)
{
    // json to_send = SerializableMessageFactory::serializeGameRequest(GameInvite::GAME_INVITE, friend); // not implemented yet
    serverBridge.send(to_send);
}

// send Game Join Request (matchmaking) 
void ServerController::joinGame(int gameId)
{
    json to_send = SerializableMessageFactory::serializeQueueJoinRequest(QueueAction::JOIN_QUEUE, GameMode::CLASSIC, username, ELO); // not implemented yet
    serverBridge.send(to_send);
}

void ServerController::acceptFriendInvite(std::string username)
{
    // jsp si cest bon comme ca
    json to_send = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::ACCEPT_INVITE, username); // not implemented yet
    serverBridge.send(to_send);
}


// send register request
void ServerController::registerPlayer(std::string username, std::string password)
{
    json to_send = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::REGISTRATION, username, password);
    serverBridge.send(to_send);
}

// send logIn request
void ServerController::logIn(std::string username, std::string password)
{
    json to_send = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, username, password);
    serverBridge.send(to_send);
}


void ServerController::saveGame(std::string username)
{
    json to_send = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::PROPOSE_SAVE, username);
    serverBridge.send(to_send);
}

void ServerController::pauseGame(std::string username)
{
    // json to_send = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::ASK_PAUSE, username);
    // serverBridge.send(to_send);
}


// Work 02/03
// Deals with income from the server => sends it to the view

/* GENERAL REQUEST HANDLER */
void ServerController::processRequest(std::string message)
{
    json msg = json::parse(msg);
    
    switch (msg["domain"]) {
        case toJsonString(Domain::AUTH): 
            processAuth(serRequest);
        case toJsonString(Domain::RELATIONS): 
            processRelations(serRequest);
        case toJsonString(Domain::RESOURCE_REQUEST): 
            processResourceRequest(serRequest);
        case toJsonString(Domain::IN_GAME_RELATED): 
            processGameAction(serRequest);
        case toJsonString(Domain::GAME_SETUP): 
            processGameSetup(serRequest);
        case toJsonString(Domain::CHAT): 
            processChatbox(serRequest);
    }
}

void ServerController::processAuth(std::string message) 
{
    switch (message["action"]) {
        case toJsonString(ClientAuthAction::LOGIN):
            logInReceipt(message);      // we have to send this to the view (either succesful or nah)
        case toJsonString(ClientAuthAction::REGISTRATION):
            registerReceipt(message);   // also this to the view
    }
}

void ServerController::processRelations(std::string message) 
{
    switch (message["action"]) {
        // case toJsonString(FriendAction::FRIEND_REQUEST):
        //     sendFriendRequest(message);      
        case toJsonString(FriendAction::FRIEND_ACCEPT):
            friendAccepted(message);   
        case toJsonString(FriendAction::FRIEND_REFUSE):
            friendRefused(message);   
        // case toJsonString(FriendAction::FRIEND_REMOVE):
        //     removeFriend(message);   
    }
}

void ServerController::processResourceRequest(std::string message) 
{   
    // les ressources quon peut demander du serveur : FRIENDS_LIST, FRIEND_REQUESTS_SENT, FRIEND_REQUESTS_RECEIVED, CHATS, LEADERBOARD, GAME_IDS
    // donc ici apres avoir demander au serveur on recoit la ressource quon renvoie a la vue 
    
    switch (message["data_type"]) {     
        case toJsonString(DataType::FRIENDS_LIST):
            sendFriendsList(message);   
        case toJsonString(DataType::FRIEND_REQUESTS_SENT):
            sendfriendsRequestSentList(message);   
        case toJsonString(DataType::FRIEND_REQUESTS_RECEIVED):
            sendfriendsRequestReceivedList(message);      
        // case toJsonString(DataType::CHATS):
        //     sendChats(message); 
        //case toJsonString(DataType::GAME_IDS):
        //    sendGameIds(message);   
    }
}

void ServerController::processChatbox(std::string message) 
{
    // the servers sends us a message received from friends
    switch (message["action"]) {
    case toJsonString(ChatInteraction::FRIEND_MESSAGE):
        receiveDirectMessage(message);
    case toJsonString(ChatInteraction::IN_GAME_MESSAGE):
        receiveGroupMessage(message);
    }
}


void ServerController::processGameSetup(std::string message)
{
    // wtf is game setup ??
}

void ServerController::processGameAction(std::string message)
{
    // movePlayer(message);
    // placeWall(message);
}

/* --------- */
// send action played
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

    // std::shared_ptr<WallAction> wallAction {board, dictPlayer[playerColor], end_position / 2, wallOrientation};

    // wallAction->executeAction();
    // if (wallAction->isGameOver()) isGameOver(true);
}

// send message received
json ServerController::receiveGroupMessage(std::string msg)
{
    // DatabaseHandler::recordMessage(request["sender"], request["message"], request["game_id"]); 
    isGroupMessageReceived(true);
    return json::parse(msg);
}

json ServerController::receiveDirectMessage(std::string msg)
{
    // DatabaseHandler::recordMessage(request["sender"], request["receiver"], request["message"]); 

    isDirectMessageReceived(true);
    return json::parse(msg);
}

// methods to add here :
// logInReceipt
// registerReceipt
// 
// sendFriendRequest
// friendAccepted
// friendRefused
// removeFriend
// 
// sendFriendsList
// sendfriendsRequestSentList
// sendfriendsRequestReceivedList
// sendChats
// sendGameIds
// 
// receiveGroupMessage (update)
// receiveDirectMessage (update)
//
