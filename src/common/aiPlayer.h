//
// Created by louis on 3/21/22.
//

#pragma once
#include "src/client/Board.h"
#include "src/client/Player.h"
#include "src/client/PlayerAction.h"
#include "src/client/WallAction.h"
#include "src/client/WallEnum.h"

class aiPlayer
{
    //    PlayerAction bestMove;
    std::shared_ptr<PlayerAction> bestMove;
    WallAction findWallPlacement(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, WallOrientation orientation);
    static int distanceFromFinishLine(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player);
    int minimax(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai, int depth, bool maximizing);
    static std::vector<PlayerAction> getValidActions(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player);

public:
    static bool isGameOver(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player);
    PlayerAction findAction(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai);
    void play(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai);
};
