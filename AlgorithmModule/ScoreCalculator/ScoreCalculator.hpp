#pragma once

#include "IScoreCalculator.hpp"

#include <memory>

class ScoreCalculator: public IScoreCalculator
{
public:
    static std::unique_ptr<ScoreCalculator> Instance(const LettersInfo& lettersInfo);
    std::vector<ScoreCalculatorResult> calculateScores(const ScoreCalculatorQuery& query) override;

private:
    ScoreCalculator(const LettersInfo& lettersInfo);
    bool isNewWordCreated(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position, Orientation orientation) const;
    std::vector<WordPlacement> findAllCreatedWords(const WordPlacement& word, const GameBoard& gameBoard) const;
    std::size_t calculateRawWordScore(const ScrabbleString& str) const;
    std::size_t calculateResultScore(const WordPlacement& word, const GameBoard& gameBoard) const;
    bool isAllLettersUsed(const WordPlacement& word, const GameBoard& gameBoard) const;
    LettersInfo lettersInfo_;
};
