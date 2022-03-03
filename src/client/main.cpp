/**
 * @file main.cpp
 * @author Kourieh Anne-Marie (and Gamboa Dos Santos Léo)
 * @brief main.cpp plays the game when the player clicks on start game (Idea but don't know how to call this)
 * @date 2022-02-25
*/

#include "Board.h"
#include "Player.h"
#include "PlayerAction.h"
#include "../common/Point.h"
#include "ViewController.h"
#include "ServerController.h"


#include <memory>
#include <vector>
#include <iostream>
int main()
{
    /*
    std::shared_ptr<Board> board = std::make_shared<Board>();
    std::shared_ptr<Board> board2 = std::make_shared<Board>();

    auto player = std::make_shared<Player>(PawnColors::Blue, Point{0,0}, 99, FinishLine::South, "pippo");
    auto player2 = std::make_shared<Player>(PawnColors::Purple, Point{4,4}, 99, FinishLine::North, "topolino");
    auto player3 = std::make_shared<Player>(PawnColors::Yellow, Point{2,2}, 99, FinishLine::East, "pluto");

    board->spawnPlayer(player);
    board->spawnPlayer(player2);
    board->spawnPlayer(player3);
    board->placeWall(Point{1,1}, WallOrientation::Vertical);
    WallAction action_v {board, player, Point {1, 1}, WallOrientation::Vertical};

     //   action_v.executeAction();

  //  std::cout << board->serialized().dump(4);

        std::string a = board->serialized().dump(4);
        //std::cout << board->serialized().dump();
        board2->deserialized(a);
        board2->debugPrint();
    */
     return 0;

}