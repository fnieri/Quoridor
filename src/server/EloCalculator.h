#pragma once

/**
 * @file EloCalculator.h
 * @author Francesco Nieri
 * @brief Calculate ELO at the end of a match
 * @version 0.1
 * @date 2022-02-20
 * 
 * 
 */

#include "../common/User.h"
#include <vector>

// Look in SRD for precise step by step procedure of ELO calculation

class EloCalculator
{
    std::vector<User> users;
    std::vector<float> startingELOs;
    std::vector<float> transformedScores;
    std::vector<float> expectedScores;
    std::vector<float> finalELOs;
    std::vector<bool> hasWon;   // Vector representing whether a user ha wons 
    int KFactor = 32;

    /**
     * @brief Calculate transformed scores for all players
     * 
     */
    void calculateTransformedScore();
    /**
     * @brief calculate expected socres for 2 players game
     * push_back result to expectedScores
     * 
     */
    void calculateTwoPlayersExpectedScore();
    /**
     * @brief Calculate expected scores for 4 players game
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
     * @brief Calculate final ELOs for all involved player
     * push_back to finalELOs vector
     * 
     */
    void calculateFinalELOs();
public:

    EloCalculator(std::vector<User> users, std::vector<bool> hasWon);
    
    /** Function that launches all auxiliary functions to calculate
     * ELO based on the number of players
     */
    void calculateELO();
    
    std::vector<float> getFinalELOs();
};