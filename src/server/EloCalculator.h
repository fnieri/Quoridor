#pragma once

#include "../common/User.h"
#include <vector>

// Look in SRD for precise step by step procedure of ELO calculation
// Written by Francesco Nieri

class EloCalculator
{
    std::vector<User> users;
    std::vector<float> startingELOs;
    std::vector<float> transformedScores;
    std::vector<float> expectedScores;
    std::vector<float> finalELOs;
    std::vector<bool> hasWon;
    int KFactor = 32;

public:
    EloCalculator(std::vector<User> users, std::vector<bool> hasWon);
    void calculateELO();
    void calculateTransformedScore();
    void calculateTwoPlayersExpectedScore();
    void calculateFourPlayersExpectedScore();
    void calculateFinalScore();
    float calculateFourPlayerDenumerator(int player);
    float calculateOmega(float player1ELO, float player2ELO);
    void calculateFinalELOs();
};