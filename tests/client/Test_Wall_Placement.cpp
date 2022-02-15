

#include <catch2/catch.hpp>

#include "src/client/Board.h"
#include "src/client/Player.h"
#include "src/client/WallAction.h"

#include <memory>

SCENARIO("Valid wall placements")
{
    std::shared_ptr<Player> p(new Player {PawnColors::Blue, Point {0, 0}, 10});
    std::shared_ptr<Board> b(new Board {});

    WallAction action_a {b, p, Point {0, 0}, WallOrientation::Vertical};
    WallAction action_b {b, p, Point {0, 1}, WallOrientation::Vertical};
    WallAction action_c {b, p, Point {0, 0}, WallOrientation::Horizontal};
    WallAction action_d {b, p, Point {0, 2}, WallOrientation::Vertical};
    WallAction action_e {b, p, Point {2, 2}, WallOrientation::Horizontal};
    WallAction action_f {b, p, Point {1, 2}, WallOrientation::Horizontal};

    GIVEN("Empty board")
    {
        REQUIRE(action_a.isWallPlacementValid());
        REQUIRE(action_a.executeAction());
        REQUIRE(action_e.isWallPlacementValid());
        REQUIRE(action_e.executeAction());
    }

    // On board now: a, e

    GIVEN("Identical walls")
    {
        REQUIRE(!action_a.isWallPlacementValid());
        REQUIRE(!action_a.executeAction());
        REQUIRE(!action_e.isWallPlacementValid());
        REQUIRE(!action_e.executeAction());
    }

    GIVEN("Overlapping walls")
    {
        REQUIRE(!action_b.isWallPlacementValid());
        REQUIRE(!action_b.executeAction());
        REQUIRE(!action_f.isWallPlacementValid());
        REQUIRE(!action_f.executeAction());
    }

    WallAction action_x {b, p, Point {0, 1}, WallOrientation::Horizontal};
    WallAction action_y {b, p, Point {1, 0}, WallOrientation::Horizontal};
    WallAction action_z {b, p, Point {1, 1}, WallOrientation::Vertical};

    GIVEN("Touching walls")
    {
        REQUIRE(action_x.isWallPlacementValid());
        REQUIRE(action_x.executeAction());
        REQUIRE(action_y.isWallPlacementValid());
        REQUIRE(action_y.executeAction());
        REQUIRE(action_z.isWallPlacementValid());
        REQUIRE(action_z.executeAction());
    }

    // On board now: a, e, x, y, z

    std::shared_ptr<Player> p2(new Player {PawnColors::Green, Point {0, 0}, 1});

    WallAction action_u {b, p2, Point {0, 4}, WallOrientation::Horizontal};
    WallAction action_v {b, p2, Point {0, 5}, WallOrientation::Horizontal};

    GIVEN("Player out of walls")
    {
        REQUIRE(action_u.isWallPlacementValid());
        REQUIRE(action_u.executeAction());
        REQUIRE(!action_v.isWallPlacementValid());
        REQUIRE(!action_v.executeAction());
    }

    std::shared_ptr<Player> p3(new Player {PawnColors::Green, Point {0, 0}, 10});
    std::shared_ptr<Board> b2(new Board {});

    WallAction action_o1 {b2, p3, Point {-1, 0}, WallOrientation::Horizontal};
    WallAction action_o2 {b2, p3, Point {0, -1}, WallOrientation::Vertical};
    WallAction action_o3 {b2, p3, Point {b2->getCellSize() - 1, 0}, WallOrientation::Horizontal};
    WallAction action_o4 {b2, p3, Point {0, b2->getCellSize() - 1}, WallOrientation::Vertical};
    WallAction action_o5 {b2, p3, Point {0, b2->getCellSize() - 1}, WallOrientation::Horizontal};
    WallAction action_o6 {b2, p3, Point {b2->getCellSize() - 1, 0}, WallOrientation::Vertical};
    WallAction action_o7 {b2, p3, Point {0, b2->getCellSize() - 2}, WallOrientation::Horizontal};
    WallAction action_o8 {b2, p3, Point {b2->getCellSize() - 2, 0}, WallOrientation::Vertical};

    // Reminder: since the walls are 2-long, the last row / column cannot have walls (o5 & o6)
    GIVEN("Out of bounds wall placements")
    {
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