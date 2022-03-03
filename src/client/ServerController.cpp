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

void ServerController::setViewController(std::shared_ptr<ViewController> vController)
{
    viewController = vController;
}

bool ServerController::isGameOver(bool over)
{
    return over;
}


/* GENERAL REQUEST SENDER */

void ServerController::sendPlayerAction(PlayerAction action, int playerId)
{
    json to_send = SerializableMessageFactory::serializePawnAction(action, playerId);   
    serverBridge.send(to_send);
}

void ServerController::sendWallAction(WallAction action, int playerId)
{
    json to_send = SerializableMessageFactory::serializeWallAction(action, playerId);  
    serverBridge.send(to_send);
}

void ServerController::sendDirectMessage(std::string sender, std::string receiver, std::string msg)
{
    json to_send = SerializableMessageFactory::serializeFriendMessage(sender, receiver, msg);   // make a json formated message
    serverBridge.send(to_send);
}

void ServerController::sendGroupMessage(std::string sender, std::string msg, int gameId)
{
    // find all receivers ? not understood
    // json to_send = SerializableMessageFactory::serializeInGameMessage(sender, receivers, msg, gameID);
    // serverBridge.send(to_send);
}

void ServerController::sendDMChatBoxRequest(std::string sender, std::string receiver)
{
    json to_send = ObjectExchangesSerializableMessageFactory::serializeFriendChatRequest(sender, receiver);
    serverBridge.send(to_send);
}


void ServerController::sendFriendRequest(std::string sender, std::string receiver)
{
    json to_send = SerializableMessageFactory::serializeFriendRequest(FriendAction::FRIEND_REQUEST, sender, receiver);
    serverBridge.send(to_send);
}

void ServerController::sendLeaderboardRequest()
{
    json to_send = SerializableMessageFactory::serializeRequestExchange(DataType::LEADERBOARD);
    serverBridge.send(to_send);
}

// TODO SERIALIZE INVITE
void ServerController::sendInvite(std::string aFriend)
{
    // json to_send = SerializableMessageFactory::serializeGameRequest(GameInvite::GAME_INVITE, friend); 
    // serverBridge.send(to_send);
}

// send Game Join Request (matchmaking) + TODO SERIALIZE
/*
void ServerController::joinGame(std::string gameSetup, int ELO, std::string username)
{
    json to_send = SerializableMessageFactory::serializeQueueJoinRequest(QueueAction::JOIN_QUEUE, GameMode::CLASSIC, username, ELO); // not implemented yet
    serverBridge.send(to_send);
}*/

void ServerController::acceptFriendInvite(std::string username)
{
    // jsp si cest bon comme ca
    json to_send = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::ACCEPT_INVITE, username); // not implemented yet
    serverBridge.send(to_send);
}


// send register request
void ServerController::sendRegisterRequest(std::string username, std::string password)
{
    json to_send = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::REGISTRATION, username, password);
    serverBridge.send(to_send);
}

// send logIn request
void ServerController::sendLogInRequest(std::string username, std::string password)
{
    json to_send = SerializableMessageFactory::serializeUserRequest(ClientAuthAction::LOGIN, username, password);
    serverBridge.send(to_send);
}


void ServerController::sendSaveGameRequest(std::string username)
{
    json to_send = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::PROPOSE_SAVE, username);
    serverBridge.send(to_send);
}

// TODO SERIALIZE PAUSE
void ServerController::sendPauseRequest(std::string username)
{
    // json to_send = SerializableMessageFactory::serializeInGameRelatedRequest(GameAction::ASK_PAUSE, username);
    // serverBridge.send(to_send);
}


// Work 02/03
// Deals with income from the server => sends it to the view

/* GENERAL REQUEST HANDLER */
// Method inspired by Boris' UserHandler::processRequest method
void ServerController::processRequest(std::string message)
{
    auto request(json::parse(message));

    if (request["domain"] == toJsonString(Domain::AUTH)) {
        processAuth(message);

    } else if (request["domain"] == toJsonString(Domain::RELATIONS)) {
        processRelations(message);

    } else if (request["domain"] == toJsonString(Domain::CHAT)) {
        processChatbox(message);

    } else if (request["domain"] == toJsonString(Domain::RESOURCE_REQUEST)) {
        processResourceRequest(message);

    } else if (request["domain"] == toJsonString(Domain::IN_GAME_RELATED)) {
        processGameAction(message);

    } else if (request["domain"] == toJsonString(Domain::GAME_SETUP)) {
        processGameSetup(message);
    }
}

void ServerController::processAuth(std::string message) 
{
    auto request(json::parse(message));
    if (request["action"] == toJsonString(ClientAuthAction::LOGIN))
        logInReceipt(message);      // we have to send this to the view (either succesful or nah)
    else if (request["action"] == toJsonString(ClientAuthAction::REGISTRATION))
        registerReceipt(message);   // also this to the view
}

void ServerController::processRelations(std::string message) 
{
    auto request(json::parse(message));

    if (request["action"] == toJsonString(FriendAction::FRIEND_ACCEPT))
        friendRequestReceipt(message);    
    else if (request["action"] == toJsonString(FriendAction::FRIEND_REFUSE))
        friendRequestReceipt(message);   

    // case toJsonString(FriendAction::FRIEND_REMOVE):
    //     removeFriend(message);   
    // case toJsonString(FriendAction::FRIEND_REQUEST):
    //     sendFriendRequest(message);  
}

void ServerController::processResourceRequest(std::string message) 
{   
    // les ressources quon peut demander du serveur : FRIENDS_LIST, FRIEND_REQUESTS_SENT, FRIEND_REQUESTS_RECEIVED, CHATS, LEADERBOARD, GAME_IDS
    // donc ici apres avoir demander au serveur on recoit la ressource quon renvoie a la vue 
    
    auto request(json::parse(message));

    if (request["data_type"] == toJsonString(DataType::FRIENDS_LIST))
        sendFriendsList(message);     
    else if (request["data_type"] == toJsonString(DataType::FRIENDS_LIST))
        sendfriendsRequestSentList(message);  
    else if (request["data_type"] == toJsonString(DataType::FRIEND_REQUESTS_RECEIVED))
        sendfriendsRequestReceivedList(message);      

    // case toJsonString(DataType::CHATS):
    //     sendChats(message); 
    //case toJsonString(DataType::GAME_IDS):
    //    sendGameIds(message);   
}

void ServerController::processChatbox(std::string message) 
{
    auto request(json::parse(message));

    if (request["action"] == toJsonString(ChatInteraction::FRIEND_MESSAGE))
        receiveDirectMessage(message);
    else if (request["action"] == toJsonString(ChatInteraction::IN_GAME_MESSAGE))
        receiveGroupMessage(message);
}


void ServerController::processGameSetup(std::string message)
{
    // wtf process game setup ??
}

void ServerController::processGameAction(std::string message)
{
    auto request(json::parse(message));

    if (request["action"] == toJsonString(JsonPlayerAction::PLACE_WALL))
        placeWallReceipt(message);
    else if (request["action"] == toJsonString(JsonPlayerAction::MOVE_PAWN))
        movePlayerReceipt(message);
}

void ServerController::receiveGroupMessage(std::string msg)
{
    viewController->receiveGroupMessage(msg);
}

void ServerController::receiveDirectMessage(std::string msg)
{
    viewController->receiveDirectMessage(msg);
}

void ServerController::logInReceipt(std::string msg)
{
    viewController->logInReceipt(msg);
}

void ServerController::registerReceipt(std::string msg)
{
    viewController->registerReceipt(msg);
}

void ServerController::friendRequestReceipt(std::string msg)
{
    viewController->friendRequestReceipt(msg);
}

void ServerController::sendFriendsList(std::string msg)
{
    viewController->sendFriendsList(msg);
}

void ServerController::sendfriendsRequestSentList(std::string msg)
{
    viewController->sendfriendsRequestSentList(msg);
}

void ServerController::sendfriendsRequestReceivedList(std::string msg)
{
    viewController->sendfriendsRequestReceivedList(msg);
}
 
// These need to be sent first from the server...
// removeFriend

// sendChats
// sendGameIds

// Only these to are sent immediatly to the model not the view
void ServerController::movePlayerReceipt(std::string action)
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

void ServerController::placeWallReceipt(std::string action)
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
