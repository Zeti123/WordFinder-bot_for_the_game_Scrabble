#pragma once

#include "GameBoard.hpp"
#include "ScrabbleString.hpp"

class ScrabbleSearchEngineQuery
{
public:
    ScrabbleSearchEngineQuery(const GameBoard& gameBoard, const ScrabbleString& userLetters);
    GameBoard gameBoard;
    ScrabbleString userLetters;
};
