#pragma once

#include <utility>

#include "ScrabbleString.hpp"

enum class Orientation
{
    VERTICAL, HORIZONTAL
};

struct WordPlacement
{
    WordPlacement(const ScrabbleString& word, std::pair<uint8_t, uint8_t> position, Orientation orientation);

    ScrabbleString word;
    std::pair<uint8_t, uint8_t> position;
    Orientation orientation;
};

std::ostream& operator << (std::ostream& ostream, Orientation orientation);
std::ostream& operator << (std::ostream& ostream, const WordPlacement& wordPlacement);
