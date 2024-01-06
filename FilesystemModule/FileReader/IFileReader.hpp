#pragma once

#include "Trie.hpp"

#include <QString>
#include <vector>

class IFileReader
{
public:
    virtual ~IFileReader() = default;
    virtual std::vector<QString> readWordsFile(const QString& filename) = 0;
    virtual std::vector<std::pair<QChar, std::size_t>> readLettersInfoFile(const QString& filename) = 0;
};

