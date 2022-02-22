
#include <catch2/catch.hpp>

#include "src/client/Board.h"
#include "src/client/PlayerAction.h"
#include "src/client/WallAction.h"

#include <iostream>
#include <memory>

TEST_CASE("Valid Player Move")
{
    std::shared_ptr<Board> b(new Board {});
    std::shared_ptr<Player> player(new Player {PawnColors::Blue, Point {4, 6}, 99});

    SECTION("Basic move")
    {
        PlayerAction a1 {b, player, {2, 2}}; // go up
        PlayerAction a2 {b, player, {2, 4}}; // go down
        PlayerAction a3 {b, player, {3, 3}}; // go right
        PlayerAction a4 {b, player, {1, 3}}; // go left

        REQUIRE(a1.isActionValid());
        REQUIRE(a2.isActionValid());
        REQUIRE(a3.isActionValid());
        REQUIRE(a4.isActionValid());
        REQUIRE(a2.executeAction());
        REQUIRE(b->isFree({4, 6}));
        REQUIRE(!b->isFree({4, 8}));
    }
    SECTION("Jump Move with free way")
    {
        std::shared_ptr<Player> player2(new Player {PawnColors::Yellow, Point {6, 4}, 99});

        PlayerAction a5 {b, player, {2, 3}};
        PlayerAction a6 {b, player2, {2, 2}};

        REQUIRE(a5.isActionValid());
        REQUIRE(a5.executeAction());
        REQUIRE(a6.isActionValid());
        REQUIRE(a6.executeAction());

        PlayerAction a7 {b, player, {2, 1}}; // Jump

        REQUIRE(a7.isActionValid());
    }
    SECTION("Diagonal move")
    {
        std::shared_ptr<Player> player2(new Player {PawnColors::Green, Point {8, 4}, 99});
        PlayerAction a8 {b, player2, {3, 2}};
        PlayerAction a9 {b, player, {3, 3}};
        REQUIRE(a8.isActionValid());
        REQUIRE(a8.executeAction());
        REQUIRE(a9.isActionValid());
        REQUIRE(a9.executeAction());

        PlayerAction a10 {b, player, {4, 2}};
        PlayerAction a11 {b, player, {2, 2}};
        PlayerAction a12 {b, player2, {2, 3}};
        PlayerAction a13 {b, player2, {4, 3}};
        REQUIRE(a10.isActionValid());
        REQUIRE(a11.isActionValid());
        REQUIRE(a12.isActionValid());
        REQUIRE(a13.isActionValid());

        SECTION("Diagonal move with wall")
        {
            WallAction a14(b, player, Point {2, 1}, WallOrientation::Vertical);
            WallAction a15(b, player, Point {4, 2}, WallOrientation::Horizontal);

            REQUIRE(a14.isWallPlacementValid());
            REQUIRE(a14.executeAction());
            REQUIRE(a15.isWallPlacementValid());
            REQUIRE(a15.executeAction());
            REQUIRE(a10.isActionValid());
            REQUIRE(a12.isActionValid());
            REQUIRE_FALSE(a11.isActionValid());

            std::shared_ptr<Player> player3(new Player {PawnColors::Blue, Point {10, 6}, 99});

            PlayerAction a16 {b, player3, {4, 3}};
            REQUIRE(a16.isActionValid());
            REQUIRE(a16.executeAction());
            REQUIRE(a10.isActionValid());
        }
    }
}

TEST_CASE("Player Move not valid")
{
    std::shared_ptr<Board> b(new Board {});
    std::shared_ptr<Player> player(new Player {PawnColors::Blue, Point {4, 6}, 99});

    SECTION("Basic Move : invalid")
    {

        SECTION("Move to far with no occupied cell between jump")
        {
            PlayerAction a1 {b, player, {2, 1}};
            REQUIRE(!a1.isActionValid());
        }

        SECTION("Diagonal move with no occupied cell next to")
        {
            PlayerAction a2 {b, player, {3, 4}};
            REQUIRE(!a2.isActionValid());
        }

        SECTION("Move to an occupied cell")
        {
            std::shared_ptr<Player> p(new Player {PawnColors::Green, Point {2, 6}, 99});
            PlayerAction a3 {b, p, {1, 3}};
            PlayerAction a4 {b, player, {1, 3}};
            REQUIRE(a3.isActionValid());
            REQUIRE(a3.executeAction());
            REQUIRE(!a4.isActionValid());
        }
    }

    SECTION("Way blocked by wall")
    {
        WallAction w1 {b, player, Point {2, 3}, WallOrientation::Vertical};
        PlayerAction a4 {b, player, {3, 3}};
        REQUIRE(w1.isWallPlacementValid());
        REQUIRE(w1.executeAction());
        REQUIRE(!a4.isActionValid());
    }

    SECTION("Jump move : invalid")
    {

        std::shared_ptr<Player> player2(new Player {PawnColors::Yellow, Point {6, 4}, 99});

        PlayerAction a5 {b, player, {2, 3}};
        PlayerAction a6 {b, player2, {2, 2}};

        REQUIRE(a5.isActionValid());
        REQUIRE(a5.executeAction());
        REQUIRE(a6.isActionValid());
        REQUIRE(a6.executeAction());

        SECTION("BLocked by a first wall")
        {
            WallAction a7 {b, player, Point {2, 2}, WallOrientation::Horizontal};
            PlayerAction a8 {b, player, {2, 1}}; // Jump
            REQUIRE(a7.isWallPlacementValid());
            REQUIRE(a7.executeAction());
            REQUIRE(!a8.isActionValid());
        }

        SECTION("Blocked by another wall")
        {
            WallAction a9 {b, player, Point {2, 1}, WallOrientation::Horizontal};
            PlayerAction a10 {b, player, {2, 1}}; // Jump
            REQUIRE(a9.isWallPlacementValid());
            REQUIRE(a9.executeAction());
            REQUIRE(!a10.isActionValid());
        }
        SECTION("Jump too far")
        {
            PlayerAction a11 {b, player, {2, 0}};
            REQUIRE(!a11.isActionValid());
        }
        SECTION("Jump into occupied cell")
        {
            std::shared_ptr<Player> player3(new Player {PawnColors::Green, Point {6, 2}, 99});
            PlayerAction a12 {b, player3, {2, 1}};
            REQUIRE(a12.isActionValid());
            REQUIRE(a12.executeAction());
            PlayerAction a13 {b, player, {2, 1}}; // jump
            REQUIRE(!a13.isActionValid());
        }
    }

    SECTION("Diagonal move : not valid")
    {
        std::shared_ptr<Player> player2(new Player {PawnColors::Green, Point {10, 6}, 99});
        PlayerAction a14 {b, player2, {4, 3}};
        PlayerAction a15 {b, player, {3, 3}};
        REQUIRE(a14.isActionValid());
        REQUIRE(a14.executeAction());
        REQUIRE(a15.isActionValid());
        REQUIRE(a15.executeAction());

        SECTION("Diagonal move blocked by wall")
        {
            WallAction a16 {b, player, Point {4, 2}, WallOrientation::Horizontal};
            PlayerAction a17 {b, player, {4, 2}};

            REQUIRE(a16.isWallPlacementValid());
            REQUIRE(a16.executeAction());
            REQUIRE(!a17.isActionValid());

            SECTION("Diagonal move blocked by another wall")
            {
                WallAction a18 {b, player, Point {3, 2}, WallOrientation::Vertical};
                REQUIRE(a18.isWallPlacementValid());
                REQUIRE(a18.executeAction());
                REQUIRE(!a17.isActionValid());
            }
        }
    }
}