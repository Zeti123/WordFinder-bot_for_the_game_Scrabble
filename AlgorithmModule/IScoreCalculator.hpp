#pragma once

#include "ScoreCalculatorResult.hpp"
#include "ScoreCalculatorQuery.hpp"

class IScoreCalculator
{
public: 
    virtual std::vector<ScoreCalculatorResult> calculateScores(const ScoreCalculatorQuery& query) = 0;
    virtual ~IScoreCalculator() = default;
};