#pragma once

#include "ScrabbleString.hpp"
#include "GameBoard.hpp"
#include "LettersInfo.hpp"

class ScoreCalculatorQuery
{
public:
    ScoreCalculatorQuery(const GameBoard& gameBoard, const std::vector<WordPlacement>& words);

    GameBoard gameBoard;
    std::vector<WordPlacement> words;
};