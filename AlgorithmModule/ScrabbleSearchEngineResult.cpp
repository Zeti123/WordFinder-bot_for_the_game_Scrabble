#include "ScrabbleSearchEngineResult.hpp"

ScrabbleSearchEngineResult::ScrabbleSearchEngineResult(const WordPlacement& word, std::size_t score)
    :word(word), score(score) { }