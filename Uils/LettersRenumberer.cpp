#include "LettersRenumberer.hpp"

#include <stdexcept>

LettersRenumberer::LettersRenumberer(const std::vector<wchar_t>& letters)
    :numToLetter_({}), letterToNum_({}), counter_(0)
{
    for (auto letter: letters)
    {
        if (counter_ >= 256)
            std::runtime_error("alphabet cannot have more than 256 different letters");

        numToLetter_[counter_] = letter;
        letterToNum_[letter] = counter_;
        counter_++;
    }
}

wchar_t LettersRenumberer::getLetterFromNum(uint8_t num)
{
    if (numToLetter_[num] == '\0')
        std::runtime_error("there is no letter with num: " + std::to_string(num));

    return numToLetter_[num];
}

uint8_t LettersRenumberer::getNumFromLetter(wchar_t letter)
{
    if (letterToNum_.find(letter) == letterToNum_.end())
        std::runtime_error("there is no letter: " + std::to_string(letter));

    return letterToNum_[letter];
}

bool LettersRenumberer::isNumberValid(uint8_t num)
{
    return num < counter_;
}

bool LettersRenumberer::isLetterValid(wchar_t letter)
{
    return letterToNum_.find(letter) != letterToNum_.end();
}
