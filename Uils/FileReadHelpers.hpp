#ifndef FILEREADHELPERS_HPP
#define FILEREADHELPERS_HPP

#include <memory>

#include "ILettersRenumberer.hpp"
#include "LettersInfo.hpp"
#include "FileReader.hpp"
#include "LanguageInfo.hpp"

LettersInfo getLettersInfo(const LanguageInfo& languageInfo, std::shared_ptr<ILettersRenumberer> renumberer);
std::vector<char32_t> getAllLetters(const LanguageInfo& languageInfo);
std::vector<std::string> convertFromQStringVector(const std::vector<QString>& words, std::shared_ptr<ILettersRenumberer> renumberer);

#endif // FILEREADHELPERS_HPP
