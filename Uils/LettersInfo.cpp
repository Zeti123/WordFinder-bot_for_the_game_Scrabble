#include "LettersInfo.hpp"
#include "log.hpp"

LettersInfo::LettersInfo(const std::vector<std::pair<char, std::size_t>>& letters)
    :letterScore_({})
{
    logger::debug("LettersInfo::LettersInfo(", letters, ")");
    for (auto letterInfo: letters)
    {
        logger::debug("letter \'", static_cast<std::size_t>(letterInfo.first), "\' score set to: ", letterInfo.second, "\n");
        letterScore_[static_cast<std::size_t>(letterInfo.first)] = letterInfo.second;
    }
}

void LettersInfo::addLetterInfo(char letter, std::size_t score)
{
    letterScore_[static_cast<std::size_t>(letter)] = score;
}

std::size_t LettersInfo::getLetterScore(char letter) const
{
    logger::debug("LettersInfo::getLetterScore(char(", std::to_string(letter), ")) score is: ",
                 std::to_string(letterScore_[static_cast<std::size_t>(letter)]), "\n");
    return letterScore_[static_cast<std::size_t>(letter)];
}

std::vector<char> LettersInfo::getAllLetters() const
{
    std::vector<char> ret = {};
    for (std::size_t i = 0; i < 256; i++)
    if (letterScore_[i] != 0)
        ret.push_back(i);

    return ret;
}
