#pragma once

#include<string>


class WallAction
{
private:
    std::string wallAction;
public:
    WallAction(/* args */);
    bool isWallPlacementLegal();
    bool isWallPlacementValid();
    ~WallAction();
};

