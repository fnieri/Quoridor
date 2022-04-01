//
// Created by louis on 3/21/22.
//

#include "aiPlayer.h"
#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <unistd.h>

std::vector<PlayerAction> aiPlayer::getValidActions(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player)
{
    std::vector<PlayerAction> validActions;
    const std::vector<Point> possibleDirections {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (auto &d : possibleDirections) {
        auto playerPos = player->getPosition();
        auto newPos = playerPos + d;
        PlayerAction action(board, player, newPos);
        if (action.isActionValid()) {
            validActions.push_back(action);
        }
    }
    return validActions;
}

int aiPlayer::distanceFromFinishLine(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player)
{
    auto playerPos = player->getPosition();
    auto copyBoard = std::make_shared<Board>(*board);
    auto finishLine = player->getFinishLine();
    int distance = 0;
    std::vector<Point> tryDirections;
    switch (finishLine) {
    case FinishLine::North:
        tryDirections = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
        break;
    case FinishLine::East:
        tryDirections = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
        break;
    case FinishLine::South:
        tryDirections = {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};
        break;
    case FinishLine::West:
        tryDirections = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
        break;
    }

    std::shared_ptr<PlayerAction> action = std::make_shared<PlayerAction>(copyBoard, player, playerPos);
    while (!action->isGameOver()) {
        while (!action->isActionValid()) {
            for (auto &d : tryDirections) {
                playerPos = playerPos + d;
                action = std::make_shared<PlayerAction>(copyBoard, player, playerPos);
                if (action->isActionValid()) {
                    break;
                }
            }
            return 100;
        }
        action->executeAction();
        distance++;
    }
    return distance;
}

std::vector<WallAction> aiPlayer::findWallPlacement(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, WallOrientation orientation)
{
    srand(time(NULL));
    auto boardSize = board->getCellSize();
    std::vector<WallAction> actions;
    int randX = rand() % boardSize;
    int randY = rand() % boardSize;
    Point wallPos(randX, randY);
    WallAction wallAction(board, player, wallPos, orientation);
    while (!wallAction.isWallPlacementValid() || actions.size() < 1) {
        randX = rand() % boardSize;
        randY = rand() % boardSize;
        wallPos = Point(randX, randY);
        wallAction = WallAction(board, player, wallPos, orientation);
        if (wallAction.isWallPlacementValid() && wallAction.isWallPlacementLegal())
            actions.push_back(wallAction);
    }
    return actions;
}

int aiPlayer::minimax(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai, int depth, bool maximizing)
{
    if (depth == 0 || isGameOver(board, player)) {
        return distanceFromFinishLine(board, player) * -1;
    }
    int bestScore = (maximizing) ? -100 : 100;
    if (maximizing) {
        for (auto &move : getValidActions(board, ai)) {
            auto newBoard = std::make_shared<Board>(*board);
            auto destination = move.getDestination();
            PlayerAction action(newBoard, ai, destination);
            action.executeAction();
            int score = minimax(newBoard, player, ai, depth - 1, false);
            if (score >= bestScore) {
                bestScore = score;
                bestPlayerMove = std::make_shared<PlayerAction>(move);
            }
        }
    } else {
        for (auto &move : getValidActions(board, player)) {
            auto newBoard = std::make_shared<Board>(*board);
            auto destination = move.getDestination();
            PlayerAction action(newBoard, player, destination);
            action.executeAction();
            int score = minimax(newBoard, player, ai, depth - 1, true);
            if (score <= bestScore) {
                bestScore = score;
                bestPlayerMove = std::make_shared<PlayerAction>(move);
            }
        }
    }
    return bestScore;
}

int aiPlayer::wallMinimax(
    const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai, int depth, bool maximizing)
{

    if (depth == 0 || isGameOver(board, player)) {
        return distanceFromFinishLine(board, player) * -1;
    }
    int bestScore = (maximizing) ? -100 : 100;
    if (maximizing) {
        if (ai->nWalls() > 0) {
            for (auto &wallAction : findWallPlacement(board, ai, WallOrientation::Horizontal)) {

                auto newBoard = std::make_shared<Board>(*board);
                auto destCell = wallAction.getDestination();
                WallAction newAction(newBoard, ai, destCell, WallOrientation::Horizontal);
                newAction.executeAction();
                int score = wallMinimax(newBoard, player, ai, depth - 1, false);
                if (score >= bestScore) {
                    bestScore = score;
                    bestWallMove = std::make_shared<WallAction>(wallAction);
                }
            }
        }
    } else {
        if (player->nWalls() > 0) {
            for (auto &wallAction : findWallPlacement(board, player, WallOrientation::Horizontal)) {
                auto newBoard = std::make_shared<Board>(*board);
                auto destCell = wallAction.getDestination();
                WallAction newAction(newBoard, player, destCell, WallOrientation::Horizontal);

                newAction.executeAction();
                int score = wallMinimax(newBoard, player, ai, depth - 1, true);
                if (score <= bestScore) {
                    bestScore = score;
                    bestWallMove = std::make_shared<WallAction>(wallAction);
                }
            }
        }
    }
    return bestScore;
}

std::shared_ptr<Action> aiPlayer::findAction(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai)
{

    srand(time(NULL));

    int play = rand();
    if (play % 2 == 0) {
        minimax(board, player, ai, 2, true);
        return bestPlayerMove;
    } else {
        if (ai->nWalls() > 0) {
            wallMinimax(board, player, ai, 2, true);
            return bestWallMove;
        } else {
            minimax(board, player, ai, 2, true);
            return bestPlayerMove;
        }
    }
}

void aiPlayer::play(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &ai)
{
    auto action = findAction(board, player, ai);
    action->executeAction();
}

bool aiPlayer::isGameOver(const std::shared_ptr<Board> &board, const std::shared_ptr<Player> &player)
{
    PlayerAction action {board, player, player->getPosition()};
    if (action.isGameOver()) {
        return true;
    }
    return false;
}
