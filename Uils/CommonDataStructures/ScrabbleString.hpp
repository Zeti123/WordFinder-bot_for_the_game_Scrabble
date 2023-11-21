#pragma once

#include <cstdint>
#include <string>

struct ScrabbleLetter
{
    enum class Type : uint8_t
    {
        EMPTY_TILE, NORMAL_TILE
    };

    ScrabbleLetter() = default;
    ScrabbleLetter(char letter, Type type);
    Type type;
    char letter;
};

using ScrabbleString = std::basic_string<ScrabbleLetter>;

std::ostream& operator << (std::ostream& ostream, const ScrabbleLetter& letter);
std::ostream& operator << (std::ostream& ostream, const ScrabbleString& str);
bool operator == (const ScrabbleLetter& l, const ScrabbleLetter& r);
bool operator < (const ScrabbleLetter& l, const ScrabbleLetter& r);

std::string scrabbleStrToStdStr(const ScrabbleString& str);
