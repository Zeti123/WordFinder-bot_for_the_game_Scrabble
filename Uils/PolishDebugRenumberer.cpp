#include "PolishDebugRenumberer.hpp"

PolishDebugRenumberer::PolishDebugRenumberer()
    :polishLetters_({{{U'ż', 'Z'}, {U'ó', 'O'}, {U'ł', 'L'}, {U'ć', 'C'}, {U'ę', 'E'}, {U'ś', 'S'}, {U'ą', 'A'}, {U'ź', 'X'}, {U'ń', 'N'}}}){

}

wchar_t PolishDebugRenumberer::getLetterFromNum(uint8_t num)
{
    if (num >= 'a' && num <= 'z')
        return num;
    for (auto let: polishLetters_)
        if (let.second == num)
            return let.first;
}

uint8_t PolishDebugRenumberer::getNumFromLetter(wchar_t letter)
{
    if (letter >= 'a' && letter <= 'z')
        return letter;
    for (auto let: polishLetters_)
        if (let.first == letter)
            return let.second;
}

bool PolishDebugRenumberer::isNumberValid(uint8_t num)
{
    return  ((num >= 'a' && num <= 'z') || (num >= 'A' && num <= 'Z'));
}

bool PolishDebugRenumberer::isLetterValid(wchar_t letter)
{
    if (letter >= 'a' && letter <= 'z')
        return true;
    for (auto let: polishLetters_)
        if (let.first == letter)
            return true;
    return false;
}
