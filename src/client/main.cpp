#include "TerminalVue.h"
#include "nlohmann/json.hpp"
#include <QApplication>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "Board.h"
#include "MainController.h"
#include "MainModel.h"
#include "Player.h"
#include "ServerController.h"
#include "src/common/aiPlayer.h"
#include "QtVue.h"


void gameLoop()
{
    // load everything
    std::shared_ptr<Board> board = std::make_shared<Board>();
    std::vector<std::shared_ptr<Player>> players;
    int nPlayers = 2;
    std::vector<Point> startPositions {{4, 8}, {4, 0}, {0, 4}, {8, 4}};
    std::vector<FinishLine> finishLines {FinishLine::North, FinishLine::South, FinishLine::East, FinishLine::West};
    for (int i = 0; i < nPlayers; i++) {
        // TODO handle username
        auto p = std::make_shared<Player>(PawnColors(i), startPositions.at(i), 10, finishLines.at(i), "louis");

        players.push_back(p);

        board->spawnPlayer(p);
    }

    int x, y;
    aiPlayer ai {};
    while (!aiPlayer::isGameOver(board, players.at(0)) && !aiPlayer::isGameOver(board, players.at(1))) {
        board->debugPrint();
        std::cout << "--------------------------------" << std::endl;
        ai.play(board, players.at(0), players.at(1));
        sleep(1);
        board->debugPrint();
        std::cout << "--------------------------------" << std::endl;
        ai.play(board, players.at(1), players.at(0));
        sleep(1);
    }
    board->debugPrint();
}

void testGameJoin(std::string username, std::string password)
{
    MainController mainController;
    ServerController serverController {&mainController};
    serverController.login(username, password);
    sleep(1);
    auto model = mainController.getMainModel();
    std::cout << "Username: " << *model->getUsername() << std::endl;
    serverController.fetchGameIds();
    sleep(1);
    auto gameIDs = model->getGameIDs();
    for (auto &gameID : *gameIDs) {
        std::cout << "GameID: " << gameID.first << "    " << username << std::endl;
        serverController.joinGame(gameID.first, username);
        std::cout << "Joined game " << gameID.first << std::endl;
        sleep(5);
        return;
    }
}

auto launchTUI()
{
    TerminalVue vue;

    if (!vue.isConnectedToServer()) {
        std::cerr << "Could not connect to the server! That's a bummer, innit?\n";
        exit(1);
    } else {
        system("clear");
        vue.run();
    }

    std::thread t1(&TerminalVue::run, &vue);
    t1.join();

    return 0;
}

auto launchGUI(int argc, char *argv[]) -> int
{
    QApplication QuoridorApp(argc, argv);
    QtVue vue;
    vue.show();
    return QuoridorApp.exec();
}

int main(int argc, char *argv[])
{
    if (argc > 2 || (argc == 2 && strcmp(argv[1], "--no-gui") != 0)) {
        std::cout << "Usage:\n\t./client [--no-gui]\n";
        return 1;
    }

    if (argc == 2 && strcmp(argv[1], "--no-gui") == 0) {
        return launchTUI();
    } else {
        return launchGUI(argc, argv);
    }

    /* if () */
    //    MainController mainController;
    //    ServerController serverController {&mainController};
    //    //    serverController.registerUser("b", "b");
    //    //    serverController.registerUser("c", "c");
    //    //    serverController.login("b", "b");
    //    //    serverController.createGame("b", {"b", "c"});
    //    std::cout << "creating thread" << std::endl;
    //    std::thread t1(testGameJoin, "b", "b");
    //    sleep(1);
    //    std::thread t2(testGameJoin, "c", "c");
    //    t1.join();
    //    t2.join();
    //    return 0;
    //    serverController.login("testing", "testingPassword");
    //    serverController.createGame("testing", {"testing", "testingFriend"});
    //
    //    auto model = mainController.getMainModel();
    //    sleep(5);
    //    serverController.fetchGameIds();
    //    auto gameIds = model->getGameIDs();
    //    for (const auto& gameId : *gameIds) {
    //        std::cout << "Game ID: " << gameId.first << std::endl;
    //        for (const auto& player : gameId.second) {
    //            std::cout << "Player: " << player << std::endl;
    //        }
    //    }
    //    return 0;

    //    serverController.login("ok", "k");
    //        model->createAiGame();
    //        auto game = model->getCurrentGame();
    //        if (game) {
    //            game->debugPrintBoard();
    //            auto playerAction = game->getPlayerAction(Point {8, 2});
    //            game->processAction(playerAction.serialized().dump());
    //            game->debugPrintBoard();
    //            return 0;
    //        }
    //
    //    serverController.fetchData();
    //    model->getUsername();
    //    model->getFriendList();
    //    if (model->getFriendRequestsReceived()->empty()) std::cout << "No friend requests received" << std::endl;
    //    else std::cout << "Friend requests received: " << std::endl;
    //    sleep(2);
    //
    //    model->getUsername();
    //    auto friendList = model->getFriendList();
    //    for (const auto& f : *friendRequestsReceived) {
    //        std::cout << f << std::endl;
    //    }
    //    gameLoop();

    /* return 0; */
};
