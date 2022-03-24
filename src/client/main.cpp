#include "TerminalVue.h"
#include <cstdlib>
#include <iostream>
#include <map>
#include <unistd.h>
#include <vector>

#include "Board.h"
#include "MainController.h"
#include "MainModel.h"
#include "Player.h"
#include "ServerController.h"
#include "src/common/aiPlayer.h"

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

int main(int argc, char *argv[])
{
        MainController mainController;
    //    ServerController serverController {&mainController};
    //    //    serverController.login("testing", "testingPassword");
    //    serverController.login("ok", "k");
        auto model = mainController.getMainModel();
        model->createAiGame();
        auto game = model->getCurrentGame();
        if (game) {

            auto playerAction = game->getPlayerAction(Point {8, 2});
            game->processAction(playerAction.serialized().dump());
            return 0;
        }
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

//        system("clear");
        TerminalVue vue;
        vue.run();

    //        std::thread t1(&TerminalVue::run, &vue);
    //        t1.join();

    return 0;
};