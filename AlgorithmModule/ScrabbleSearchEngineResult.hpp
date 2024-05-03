#pragma once

#include "WordPlacement.hpp"

class ScrabbleSearchEngineResult
{
public:
    ScrabbleSearchEngineResult();
    ScrabbleSearchEngineResult(const WordPlacement& word, std::size_t score);
    WordPlacement word;
    std::size_t score;
};
