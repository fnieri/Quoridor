#ifndef WALL_ACTION
#define WALL_ACTION
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


#endif  //WALL_ACTION