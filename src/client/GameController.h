//
// Created by louis on 26/02/2022.
//
#pragma once

#include "Board.h"
#include "Player.h"
#include "PlayerAction.h"
#include "../common/Point.h"
#include "WallEnum.h"
#include "BoardComponent.h"
#include "WallEnum.h"
#include "Corridor.h"
#include "Cell.h"
#include "PlayerEnum.h"
#include "PlayerAction.h"
#include "WallAction.h"

#include <memory>
#include <vector>
#include <iostream>
#include <string>

class GameController
{
    std::shared_ptr<Board> board = std::make_shared<Board>();
    int nPlayers;
    std::vector<std::shared_ptr<Player>> players;
    int currentPlayerIndex = 0; // index of the current player in the vector of Players
    int gameId;
    std::string gameSetup;
    const int freeCell = 0, playerOne = 1, playerTwo = 2, playerThree = 3, playerFour = 4, emptyQuoridor = 5, occupiedVerticalQuoridor = 6,
              occupiedHorizontalQuoridor = 7;

public:
    GameController(int nPlayers, int currentPlayerIndex, int gameId);
//    VueController(int gameId); // fetch all data from the server

    std::shared_ptr<Board> getBoard();
    std::vector<std::vector<int>> getBoardAsIntMatrix();
    void updateBoardIntMatrix(std::vector<std::vector<int>> &boardIntMatrix);
    bool isMoveValid(int x, int y);
    bool isWallValid(int x, int y, int orientation);
    void movePlayer(int x, int y);
    void placeWall(int x, int y, int orientation);
};


