#pragma once

#include <vector>
#include <QString>

#include "LettersInfo.hpp"

class LanguageInfo
{
public:
    std::vector<QString> listOfWords;
    std::vector<std::pair<QChar, std::size_t>> lettersInfo;
};
