#include "ScrabbleString.hpp"

#include <ostream>

ScrabbleLetter::ScrabbleLetter(char letter, Type type)
	:type(type), letter(letter) { }

std::ostream& operator << (std::ostream& ostream, const ScrabbleLetter& letter)
{
	if (letter.type == ScrabbleLetter::Type::NORMAL_TILE)
        ostream << letter.letter;
	else
        ostream << '(' << letter.letter << ')';
	
    return ostream;
}

std::ostream& operator << (std::ostream& ostream, const ScrabbleString& str)
{
	for (const auto& letter: str)
        ostream << letter;
	
    return ostream;
}

bool operator == (const ScrabbleLetter& l, const ScrabbleLetter& r)
{
    return l.letter == r.letter;
}

bool operator < (const ScrabbleLetter& l, const ScrabbleLetter& r)
{
    return l.letter < r.letter;
}

std::string scrabbleStrToStdStr(const ScrabbleString& str)
{
    std::string res;
    res.reserve(str.size());
    for (auto letter: str)
        res.push_back(letter.letter);

    return res;
}
