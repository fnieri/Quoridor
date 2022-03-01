#pragma once

/**
 * @file EloCalculator.h
 * @author Francesco Nieri
 * @brief Calculate ELO at the end of a match
 * @note Look in SRD for precise step by step procedure of ELO calculation
 * Otherwise the source code might seem unreadable
 * @date 2022-02-20
 *
 *
 */

#include "../common/User.h"
#include <vector>

class EloCalculator
{
    std::vector<float> startingELOs;
    std::vector<float> transformedScores;
    std::vector<float> expectedScores;
    std::vector<float> finalELOs;
    std::vector<bool> hasWon; // Vector representing whether a user ha wons
    int KFactor = 32;

    /**
     * @brief Calculate transformed scores for all players
     *
     */
    void calculateTransformedScore();
    /**
     * @brief calculate expected scores for 2 players game
     * push_back result to expectedScores
     *
     */
    void calculateTwoPlayersExpectedScore();
    /**
     * @brief Calculate expected scores for a 4 players game
     * push_back result to expectedScores
     *
     */
    void calculateFourPlayersExpectedScore();

    /**
     * @brief Calculate 4 player denumerator
     *
     * @param player Player whose denumerator is to be calculated
     * @return float denumerator
     */
    float calculateFourPlayerDenumerator(int player);

    /**
     * @brief Calculate Omega as in SRD, only for 4 players matches
     *
     * @param player1ELO First player STARTING ELO
     * @param player2ELO Second player STARTING ELO
     * @return float Omega for first player
     */
    float calculateOmega(float player1ELO, float player2ELO);

    /**
     * @brief Calculate final ELOs for all involved players
     * push_back to finalELOs vector
     *
     */
    void calculateFinalELOs();

public:
    /**
     * @brief Construct a new Elo Calculator object, this may be changed as Users is not that relevant in a game
     *
     * @param startingELOs Vector of starting ELOS of players that participated in a game
     * @param hasWon Vector of bool with true or false indicating wether the user at index i has won
     * @throw Assertion error when users and hasWon is != 2 || 4 and when they're not equal in size
     */
    EloCalculator(std::vector<float> startingELOs, std::vector<bool> hasWon);

    /**
     * @brief Calculate ELO for all players involved in a Game
     *
     */
    void calculateELO();
    /**
     * @brief Return the finalELOs of the players involved in a game
     * @warning This must be called after calculateELO(), otherwise the behaviour might be undefined
     * @return std::vector<float>
     */
    std::vector<float> getFinalELOs();
};
