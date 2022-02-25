

#include <catch2/catch.hpp>

#include "src/client/Board.h"
#include "src/client/Player.h"
#include "src/client/WallAction.h"

#include <iostream>
#include <memory>

TEST_CASE("Valid wall placements")
{
    std::shared_ptr<Player> p(new Player {PawnColors::Blue, Point {0, 0}, 99, FinishLine::North});
    std::shared_ptr<Board> b(new Board {});
    
    SECTION("Vertical walls")
    {
        WallAction action_v {b, p, Point {1, 1}, WallOrientation::Vertical};

        REQUIRE(action_v.isWallPlacementValid());
        REQUIRE(action_v.executeAction());

        SECTION("Identical walls")
        {
            REQUIRE(!action_v.isWallPlacementValid());
            REQUIRE(!action_v.executeAction());
        }

        SECTION("Overlapping walls")
        {
            WallAction action_v2 {b, p, Point {1, 0}, WallOrientation::Vertical};
            WallAction action_v3 {b, p, Point {1, 2}, WallOrientation::Vertical};

            REQUIRE(!action_v2.isWallPlacementValid());
            REQUIRE(!action_v2.executeAction());
            REQUIRE(!action_v3.isWallPlacementValid());
            REQUIRE(!action_v3.executeAction());
        }

        SECTION("Crossing walls")
        {
            WallAction action_v2 {b, p, Point {1, 1}, WallOrientation::Horizontal};

            REQUIRE(!action_v2.isWallPlacementValid());
            REQUIRE(!action_v2.executeAction());
        }
    }

    SECTION("Horizontal walls")
    {
        WallAction action_h {b, p, Point {1, 1}, WallOrientation::Horizontal};

        REQUIRE(action_h.isWallPlacementValid());
        REQUIRE(action_h.executeAction());

        SECTION("Identical walls")
        {
            REQUIRE(!action_h.isWallPlacementValid());
            REQUIRE(!action_h.executeAction());
        }

        SECTION("Overlapping walls")
        {
            WallAction action_h2 {b, p, Point {0, 1}, WallOrientation::Horizontal};
            WallAction action_h3 {b, p, Point {2, 1}, WallOrientation::Horizontal};

            REQUIRE(!action_h2.isWallPlacementValid());
            REQUIRE(!action_h2.executeAction());
            REQUIRE(!action_h3.isWallPlacementValid());
            REQUIRE(!action_h3.executeAction());
        }

        SECTION("Crossing walls")
        {
            WallAction action_v2 {b, p, Point {1, 1}, WallOrientation::Vertical};

            REQUIRE(!action_v2.isWallPlacementValid());
            REQUIRE(!action_v2.executeAction());
        }
    }

    SECTION("Touching walls")
    {
        WallAction action_w {b, p, Point {0, 0}, WallOrientation::Vertical};
        WallAction action_x {b, p, Point {0, 1}, WallOrientation::Horizontal};
        WallAction action_y {b, p, Point {1, 0}, WallOrientation::Horizontal};
        WallAction action_z {b, p, Point {1, 1}, WallOrientation::Vertical};

        REQUIRE(action_w.isWallPlacementValid());
        REQUIRE(action_w.executeAction());
        REQUIRE(action_x.isWallPlacementValid());
        REQUIRE(action_x.executeAction());
        REQUIRE(action_y.isWallPlacementValid());
        REQUIRE(action_y.executeAction());
        REQUIRE(action_z.isWallPlacementValid());
        REQUIRE(action_z.executeAction());

        b->debugPrint();
    }

    // Reminder: since the walls are 2-long, the last row / column cannot have walls (o5 & o6)
    SECTION("Out of bounds wall placements")
    {
        WallAction action_o1 {b, p, Point {-1, 0}, WallOrientation::Horizontal};
        WallAction action_o2 {b, p, Point {0, -1}, WallOrientation::Vertical};
        WallAction action_o3 {b, p, Point {b->getCellSize() - 1, 0}, WallOrientation::Horizontal};
        WallAction action_o4 {b, p, Point {0, b->getCellSize() - 1}, WallOrientation::Vertical};
        WallAction action_o5 {b, p, Point {0, b->getCellSize() - 1}, WallOrientation::Horizontal};
        WallAction action_o6 {b, p, Point {b->getCellSize() - 1, 0}, WallOrientation::Vertical};
        WallAction action_o7 {b, p, Point {0, b->getCellSize() - 2}, WallOrientation::Horizontal};
        WallAction action_o8 {b, p, Point {b->getCellSize() - 2, 0}, WallOrientation::Vertical};

        REQUIRE(!action_o1.isWallPlacementValid());
        REQUIRE(!action_o1.executeAction());
        REQUIRE(!action_o2.isWallPlacementValid());
        REQUIRE(!action_o2.executeAction());
        REQUIRE(!action_o3.isWallPlacementValid());
        REQUIRE(!action_o3.executeAction());
        REQUIRE(!action_o4.isWallPlacementValid());
        REQUIRE(!action_o4.executeAction());
        REQUIRE(!action_o5.isWallPlacementValid());
        REQUIRE(!action_o5.executeAction());
        REQUIRE(!action_o6.isWallPlacementValid());
        REQUIRE(!action_o6.executeAction());
        REQUIRE(action_o7.isWallPlacementValid());
        REQUIRE(action_o7.executeAction());
        REQUIRE(action_o8.isWallPlacementValid());
        REQUIRE(action_o8.executeAction());
    }
}

TEST_CASE("Player out of walls")
{
    std::shared_ptr<Player> p(new Player {PawnColors::Green, Point {0, 0}, 1, FinishLine::North});
    std::shared_ptr<Board> b(new Board {});

    WallAction action_u {b, p, Point {0, 0}, WallOrientation::Horizontal};
    WallAction action_v {b, p, Point {0, 1}, WallOrientation::Horizontal};

    REQUIRE(action_u.isWallPlacementValid());
    REQUIRE(action_u.executeAction());
    REQUIRE(!action_v.isWallPlacementValid());
    REQUIRE(!action_v.executeAction());
}

TEST_CASE("Legal wall placements")
{
    std::shared_ptr<Board> b(new Board {});

    // SECTION("Preliminary function tests")
    // {
    //     std::shared_ptr<Player> p(new Player {PawnColors::Green, Point {0, 0}, 1});
    //     PlayerAction a {b, Player {PawnColors}, }
    // }

    // SECTION("No walls")
    // {
    //     SECTION("No walls")
    //     {
    //         std::shared_ptr<Player> p(new Player {PawnColors::Blue, Point {0, 0}, 1});
    //     }
    // }
}