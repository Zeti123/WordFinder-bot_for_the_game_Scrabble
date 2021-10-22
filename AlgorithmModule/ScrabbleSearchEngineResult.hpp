#pragma once

#include "ScrabbleString.hpp"
#include "GameBoard.hpp"

class ScrabbleSearchEngineResult
{
public:
    ScrabbleSearchEngineResult(const WordPlacement& word, std::size_t score);
    WordPlacement word;
    std::size_t score;
};