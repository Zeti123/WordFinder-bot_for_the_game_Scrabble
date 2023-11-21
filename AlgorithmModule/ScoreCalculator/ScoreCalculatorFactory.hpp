#pragma once

#include "IScoreCalculator.hpp"

#include <memory>

#include "LettersInfo.hpp"

class ScoreCalculatorFactory
{
public:
    static std::unique_ptr<IScoreCalculator> create(const LettersInfo& lettersInfo);
};
