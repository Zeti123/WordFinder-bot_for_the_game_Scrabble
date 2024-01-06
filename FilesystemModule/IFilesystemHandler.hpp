#pragma once

#include <QString>

#include "LanguageInfo.hpp"

class IFilesystemHandler
{
public:
    virtual std::vector<QString> getAvailableLanguages() = 0;
    virtual LanguageInfo getLanguageInfo(const QString& language) = 0;
};
