#pragma once

#include <string>
#include <cstdint>

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

std::ostream& operator << (std::ostream& o, const ScrabbleLetter& letter);
using ScrabbleString = std::basic_string<ScrabbleLetter>;
std::ostream& operator << (std::ostream& o, const ScrabbleString& str);
std::string scrabbleStrToStdStr(const ScrabbleString& str);
bool operator ==(const ScrabbleLetter& scl1, const ScrabbleLetter& scl2);
bool operator <(const ScrabbleLetter& scl1, const ScrabbleLetter& scl2);
