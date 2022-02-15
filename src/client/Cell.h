#pragma once

#include "BoardComponent.h"
#include "Player.h"

#include <memory>

// contains the information of a cell
class Cell : public BoardComponent
{
private:
    std::shared_ptr<Player> player;

public:
    Cell(std::shared_ptr<Player> player = nullptr);
    void placePlayer(std::shared_ptr<Player> newPlayer);
    void removePlayer();
    ~Cell();
};
