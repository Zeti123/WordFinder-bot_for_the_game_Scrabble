#ifndef FILEREADHELPERS_HPP
#define FILEREADHELPERS_HPP

#include <memory>

#include "ILettersRenumberer.hpp"
#include "LettersInfo.hpp"
#include "FileReader.hpp"

LettersInfo getLettersInfo(const std::string& filename, std::shared_ptr<ILettersRenumberer> renumberer);
std::vector<wchar_t> readFile(const std::string& filename);
std::vector<std::string> convertFromQStringVector(const std::vector<QString>& words, std::shared_ptr<ILettersRenumberer> renumberer);

#endif // FILEREADHELPERS_HPP
