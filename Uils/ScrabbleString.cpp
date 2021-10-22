#include "ScrabbleString.hpp"

#include <ostream>

ScrabbleLetter::ScrabbleLetter(char letter, Type type)
	:type(type), letter(letter) { }

std::ostream& operator << (std::ostream& o, const ScrabbleLetter& letter)
{
	if (letter.type == ScrabbleLetter::Type::NORMAL_TILE)
		o << letter.letter;
	else
		o << '(' << letter.letter << ')';
	
	return o;
}

std::ostream& operator << (std::ostream& o, const ScrabbleString& str)
{
	for (const auto& letter: str)
		o << letter;
	
	return o;
}

std::string scrabbleStrToStdStr(const ScrabbleString& str)
{
	std::string res;
	res.reserve(str.size());
	for (auto letter: str)
		res.push_back(letter.letter);

	return res;
}
bool operator== (const ScrabbleLetter& scl1, const ScrabbleLetter& scl2)
{
	return scl1.letter == scl2.letter && scl1.letter == scl2.letter;
}
