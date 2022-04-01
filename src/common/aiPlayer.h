//
// Created by louis on 3/21/22.
//

#pragma once
#include "src/client/Action.h"
#include "src/client/Board.h"
#include "src/client/Player.h"
#include "src/client/PlayerAction.h"
#include "src/client/WallAction.h"
#include "src/client/WallEnum.h"

class aiPlayer
{
    //    PlayerAction bestMove;

    std::shared_ptr<Action> bestPlayerMove;
    std::shared_ptr<Action> bestWallMove;
    /**
     * @brief Find a wall placement for AI
     *
     * @param board
     * @param player
     * @param orientation
     * @return std::vector<WallAction>
     */
    static std::vector<WallAction> findWallPlacement(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, WallOrientation orientation);
    /**
     * @brief Find the distance from the finish line of a player
     *
     * @param board
     * @param player
     * @return int
     */
    static int distanceFromFinishLine(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player);
    /**
     * @brief AI Algorithm for aiPlayer
     *
     * @param board
     * @param player
     * @param ai
     * @param depth
     * @param maximizing
     * @return int
     */
    int minimax(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai, int depth, bool maximizing);
    int wallMinimax(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai, int depth, bool maximizing);
    static std::vector<PlayerAction> getValidActions(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player);

public:
    static bool isGameOver(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player);
    std::shared_ptr<Action> findAction(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai);
    void play(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai);
};
