#include "ScoreCalculatorFactory.hpp"

#include "ScoreCalculator.hpp"

std::unique_ptr<IScoreCalculator> ScoreCalculatorFactory::create(const LettersInfo& lettersInfo)
{
    return ScoreCalculator::Instance(lettersInfo);
}
