#include "EloCalculator.h"

#include <cassert>
#include <math.h>
#include <stdexcept>
#include <string>

EloCalculator::EloCalculator(std::vector<User> users, std::vector<bool> hasWon)
    : users {users}
    , hasWon {hasWon}
{
    assert(
        ("Users and hasWon vectors must be 2 or 4 and equal in size ", (users.size() == 2 && hasWon.size() == 2) || users.size() == 4 && (hasWon.size() == 4)));
}

void EloCalculator::calculateELO()
{

    for (auto &user : users) {
        startingELOs.push_back((float)user.getELO());
    }

    calculateTransformedScore();
    if (users.size() == 2)
        calculateTwoPlayersExpectedScore();
    else if (users.size() == 4)
        calculateFourPlayersExpectedScore();
    calculateFinalELOs();
    for (int i = 0; i < users.size(); i++)
        users.at(i).setELO(finalELOs.at(i));
}

void EloCalculator::calculateTransformedScore()
{
    float currentTransformedScore;
    for (int player = 0; player < users.size(); player++) {
        currentTransformedScore = pow(10, (startingELOs.at(player) / 400.0f));
        transformedScores.push_back(currentTransformedScore);
    }
}

void EloCalculator::calculateTwoPlayersExpectedScore()
{
    float expectedDenumerator {transformedScores.at(0) + transformedScores.at(1)};
    float currentExpectedScore;
    for (int player = 0; player < 2; player++) {
        currentExpectedScore = transformedScores.at(player) / expectedDenumerator;
        expectedScores.push_back(currentExpectedScore);
    }
}

void EloCalculator::calculateFourPlayersExpectedScore()
{
    float currentExpectedScore;
    float currentDenumerator;
    for (int player = 0; player < 4; player++) {
        currentDenumerator = transformedScores.at(player) + calculateFourPlayerDenumerator(player);
        currentExpectedScore = transformedScores.at(player) / currentDenumerator;
        expectedScores.push_back(currentExpectedScore);
    }
}

float EloCalculator::calculateFourPlayerDenumerator(int player)
{
    float denumerator {0};
    float currentOmega;
    for (int currentPlayer = 0; currentPlayer < 4; currentPlayer++) {
        if (currentPlayer != player) {
            currentOmega = calculateOmega(startingELOs.at(player), startingELOs.at(currentPlayer));
            denumerator += transformedScores.at(currentPlayer) * currentOmega;
        }
    }
    return denumerator / 3;
}

float EloCalculator::calculateOmega(float player1ELO, float player2ELO)
{
    float epsilon = player1ELO - player2ELO;
    if (epsilon >= 100)
        return 1 + epsilon * pow(10, -3);
    else if (epsilon <= -100)
        return 1 - epsilon * pow(10, -3);
    else
        return 1;
}

void EloCalculator::calculateFinalELOs()
{
    int currentFinalELO;
    for (int player = 0; player < users.size(); player++) {
        currentFinalELO = startingELOs.at(player) + KFactor * ((int)hasWon.at(player) - expectedScores.at(player));
        finalELOs.push_back(currentFinalELO);
    }
}
