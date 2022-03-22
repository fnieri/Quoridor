

#include <catch2/catch.hpp>

#include "src/client/Board.h"
#include "src/client/Player.h"
#include "src/client/PlayerAction.h"
#include "src/client/WallAction.h"

#include <iostream>
#include <memory>

TEST_CASE("Valid wall placements")
{
    std::shared_ptr<Player> p(new Player {PawnColors::Blue, Point {0, 0}, 99, FinishLine::North, "a"});
    std::shared_ptr<Board> b(new Board {});

    SECTION("Vertical walls")
    {
        WallAction action_v {b, p, Point {1, 1}, WallOrientation::Vertical};

        REQUIRE(action_v.isWallPlacementValid());
        REQUIRE(action_v.executeAction());

        SECTION("Identical walls")
        {
            REQUIRE_FALSE(action_v.isWallPlacementValid());
            REQUIRE_FALSE(action_v.executeAction());
        }

        SECTION("Overlapping walls")
        {
            WallAction action_v2 {b, p, Point {1, 0}, WallOrientation::Vertical};
            WallAction action_v3 {b, p, Point {1, 2}, WallOrientation::Vertical};

            REQUIRE_FALSE(action_v2.isWallPlacementValid());
            REQUIRE_FALSE(action_v2.executeAction());
            REQUIRE_FALSE(action_v3.isWallPlacementValid());
            REQUIRE_FALSE(action_v3.executeAction());
        }

        SECTION("Crossing walls")
        {
            WallAction action_v2 {b, p, Point {1, 1}, WallOrientation::Horizontal};

            REQUIRE_FALSE(action_v2.isWallPlacementValid());
            REQUIRE_FALSE(action_v2.executeAction());
        }
    }

    SECTION("Horizontal walls")
    {
        WallAction action_h {b, p, Point {1, 1}, WallOrientation::Horizontal};

        REQUIRE(action_h.isWallPlacementValid());
        REQUIRE(action_h.executeAction());

        SECTION("Identical walls")
        {
            REQUIRE_FALSE(action_h.isWallPlacementValid());
            REQUIRE_FALSE(action_h.executeAction());
        }

        SECTION("Overlapping walls")
        {
            WallAction action_h2 {b, p, Point {0, 1}, WallOrientation::Horizontal};
            WallAction action_h3 {b, p, Point {2, 1}, WallOrientation::Horizontal};

            REQUIRE_FALSE(action_h2.isWallPlacementValid());
            REQUIRE_FALSE(action_h2.executeAction());
            REQUIRE_FALSE(action_h3.isWallPlacementValid());
            REQUIRE_FALSE(action_h3.executeAction());
        }

        SECTION("Crossing walls")
        {
            WallAction action_v2 {b, p, Point {1, 1}, WallOrientation::Vertical};

            REQUIRE_FALSE(action_v2.isWallPlacementValid());
            REQUIRE_FALSE(action_v2.executeAction());
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

        // b->debugPrint();
        /* std::cout << b->serialized().dump(); */
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

        REQUIRE_FALSE(action_o1.isWallPlacementValid());
        REQUIRE_FALSE(action_o1.executeAction());
        REQUIRE_FALSE(action_o2.isWallPlacementValid());
        REQUIRE_FALSE(action_o2.executeAction());
        REQUIRE_FALSE(action_o3.isWallPlacementValid());
        REQUIRE_FALSE(action_o3.executeAction());
        REQUIRE_FALSE(action_o4.isWallPlacementValid());
        REQUIRE_FALSE(action_o4.executeAction());
        REQUIRE_FALSE(action_o5.isWallPlacementValid());
        REQUIRE_FALSE(action_o5.executeAction());
        REQUIRE_FALSE(action_o6.isWallPlacementValid());
        REQUIRE_FALSE(action_o6.executeAction());
        REQUIRE(action_o7.isWallPlacementValid());
        REQUIRE(action_o7.executeAction());
        REQUIRE(action_o8.isWallPlacementValid());
        REQUIRE(action_o8.executeAction());
    }
}

TEST_CASE("Player out of walls")
{
    std::shared_ptr<Player> p(new Player {PawnColors::Green, Point {0, 0}, 1, FinishLine::North, "a"});
    std::shared_ptr<Board> b(new Board {});

    WallAction action_u {b, p, Point {0, 0}, WallOrientation::Horizontal};
    WallAction action_v {b, p, Point {0, 1}, WallOrientation::Horizontal};

    REQUIRE(action_u.isWallPlacementValid());
    REQUIRE(action_u.executeAction());
    REQUIRE_FALSE(action_v.isWallPlacementValid());
    REQUIRE_FALSE(action_v.executeAction());
}

TEST_CASE("Legal wall placements")
{
    Point nullPtn = Point {-1, -1};
    std::shared_ptr<Board> b(new Board {});

    SECTION("4-player scenario")
    {
        std::shared_ptr<Player> pn(new Player {PawnColors::Purple, Point {4, 0}, 99, FinishLine::South, "a"});
        std::shared_ptr<Player> pe(new Player {PawnColors::Yellow, Point {8, 4}, 99, FinishLine::West, "b"});
        std::shared_ptr<Player> ps(new Player {PawnColors::Blue, Point {4, 8}, 99, FinishLine::North, "c"});
        std::shared_ptr<Player> pw(new Player {PawnColors::Green, Point {0, 4}, 99, FinishLine::East, "d"});

        b->spawnPlayer(pn);
        b->spawnPlayer(pe);
        b->spawnPlayer(ps);
        b->spawnPlayer(pw);

        SECTION("Empty board pathfinding")
        {
            REQUIRE(b->pathExists(pn->getPosition(), FinishLine::South, nullPtn, nullPtn));
            REQUIRE(b->pathExists(pe->getPosition(), FinishLine::West, nullPtn, nullPtn));
            REQUIRE(b->pathExists(ps->getPosition(), FinishLine::North, nullPtn, nullPtn));
            REQUIRE(b->pathExists(pw->getPosition(), FinishLine::East, nullPtn, nullPtn));
        }

        SECTION("Empty board wall placing")
        {
            WallAction action_a {b, pn, Point {0, 0}, WallOrientation::Horizontal};
            WallAction action_b {b, pn, Point {0, 1}, WallOrientation::Horizontal};
            WallAction action_c {b, pn, Point {0, 2}, WallOrientation::Horizontal};

            WallAction action_d {b, pn, Point {1, 0}, WallOrientation::Vertical};
            WallAction action_e {b, pn, Point {2, 0}, WallOrientation::Vertical};
            WallAction action_f {b, pn, Point {3, 0}, WallOrientation::Vertical};

            REQUIRE(action_a.isWallPlacementLegal());
            REQUIRE(action_a.executeAction());
            REQUIRE(action_b.isWallPlacementLegal());
            REQUIRE(action_b.executeAction());
            REQUIRE(action_c.isWallPlacementLegal());
            REQUIRE(action_c.executeAction());
            REQUIRE(action_d.isWallPlacementLegal());
            REQUIRE(action_d.executeAction());
            REQUIRE(action_e.isWallPlacementLegal());
            REQUIRE(action_e.executeAction());
            REQUIRE(action_f.isWallPlacementLegal());
            REQUIRE(action_f.executeAction());
        }

        SECTION("Enclose player north")
        {
            WallAction n1 {b, pn, Point {3, 0}, WallOrientation::Vertical};
            WallAction n2 {b, pn, Point {4, 0}, WallOrientation::Vertical};
            WallAction n3 {b, pn, Point {3, 1}, WallOrientation::Horizontal};

            REQUIRE(n1.executeAction());
            REQUIRE(n2.executeAction());
            REQUIRE(b->pathExists(pn->getPosition(), FinishLine::South, nullPtn, nullPtn));
            REQUIRE_FALSE(n3.isWallPlacementLegal());
            REQUIRE_FALSE(n3.executeAction());
        }
        SECTION("Enclose player east")
        {
            WallAction e1 {b, pe, Point {7, 3}, WallOrientation::Horizontal};
            WallAction e2 {b, pe, Point {7, 4}, WallOrientation::Horizontal};
            WallAction e3 {b, pe, Point {6, 3}, WallOrientation::Vertical};

            REQUIRE(e1.executeAction());
            REQUIRE(e2.executeAction());
            REQUIRE(b->pathExists(pe->getPosition(), FinishLine::West, nullPtn, nullPtn));
            REQUIRE_FALSE(e3.isWallPlacementLegal());
            REQUIRE_FALSE(e3.executeAction());
        }
        SECTION("Enclose player south")
        {
            WallAction s1 {b, ps, Point {3, 7}, WallOrientation::Vertical};
            WallAction s2 {b, ps, Point {4, 7}, WallOrientation::Vertical};
            WallAction s3 {b, ps, Point {3, 6}, WallOrientation::Horizontal};

            REQUIRE(s1.executeAction());
            REQUIRE(s2.executeAction());
            REQUIRE(b->pathExists(ps->getPosition(), FinishLine::North, nullPtn, nullPtn));
            REQUIRE_FALSE(s3.isWallPlacementLegal());
            REQUIRE_FALSE(s3.executeAction());
        }
        SECTION("Enclose player west")
        {
            WallAction w1 {b, pw, Point {0, 3}, WallOrientation::Horizontal};
            WallAction w2 {b, pw, Point {0, 4}, WallOrientation::Horizontal};
            WallAction w3 {b, pw, Point {1, 3}, WallOrientation::Vertical};

            REQUIRE(w1.executeAction());
            REQUIRE(w2.executeAction());
            REQUIRE(b->pathExists(pw->getPosition(), FinishLine::East, nullPtn, nullPtn));
            REQUIRE_FALSE(w3.isWallPlacementLegal());
            REQUIRE_FALSE(w3.executeAction());
        }
        SECTION("Enclose player middle")
        {
            std::shared_ptr<Player> pm(new Player {PawnColors::Blue, Point {4, 4}, 99, FinishLine::North, "a"});
            b->spawnPlayer(pm);

            WallAction w1 {b, pm, Point {4, 3}, WallOrientation::Horizontal};
            WallAction w2 {b, pm, Point {3, 4}, WallOrientation::Vertical};
            WallAction w3 {b, pm, Point {4, 5}, WallOrientation::Horizontal};
            WallAction w4 {b, pm, Point {5, 4}, WallOrientation::Vertical};

            REQUIRE(w1.executeAction());
            REQUIRE(b->pathExists(pm->getPosition(), FinishLine::North, nullPtn, nullPtn));
            REQUIRE(w2.executeAction());
            REQUIRE(b->pathExists(pm->getPosition(), FinishLine::North, nullPtn, nullPtn));
            REQUIRE(w3.executeAction());
            REQUIRE(b->pathExists(pm->getPosition(), FinishLine::North, nullPtn, nullPtn));
            REQUIRE_FALSE(w4.isWallPlacementLegal());
            REQUIRE_FALSE(w4.executeAction());
        }
    }

    SECTION("The great wall")
    {
        std::shared_ptr<Player> ps(new Player {PawnColors::Blue, Point {4, 4}, 99, FinishLine::South, "b"});
        std::shared_ptr<Player> pn(new Player {PawnColors::Blue, Point {4, 3}, 99, FinishLine::North, "c"});

        REQUIRE((WallAction {b, pn, Point {0, 3}, WallOrientation::Horizontal}).executeAction());
        REQUIRE((WallAction {b, pn, Point {2, 3}, WallOrientation::Horizontal}).executeAction());
        REQUIRE((WallAction {b, pn, Point {5, 3}, WallOrientation::Horizontal}).executeAction());
        REQUIRE((WallAction {b, pn, Point {7, 3}, WallOrientation::Horizontal}).executeAction());

        REQUIRE((WallAction {b, pn, Point {3, 3}, WallOrientation::Vertical}).executeAction());
        REQUIRE((WallAction {b, pn, Point {4, 3}, WallOrientation::Vertical}).executeAction());

        // b->debugPrint();

        SECTION("Player north")
        {
            b->spawnPlayer(pn);

            REQUIRE_FALSE((WallAction {b, pn, Point {4, 2}, WallOrientation::Horizontal}).executeAction());
            REQUIRE((WallAction {b, pn, Point {4, 4}, WallOrientation::Horizontal}).executeAction());
        }
        SECTION("Player south")
        {
            b->spawnPlayer(ps);

            REQUIRE((WallAction {b, ps, Point {4, 2}, WallOrientation::Horizontal}).executeAction());
            REQUIRE_FALSE((WallAction {b, ps, Point {4, 4}, WallOrientation::Horizontal}).executeAction());
        }
    }
}
