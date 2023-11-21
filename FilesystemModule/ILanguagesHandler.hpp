#pragma once

#include <QString>
#include <vector>

class ILanguagesHandler
{
public:
    virtual ~ILanguagesHandler() = default;
    virtual std::vector<QString> getAvailableLanguages() = 0;
    virtual QString getWordsFilePath(const QString& language) = 0;
    virtual QString getLettersInfoFilePath(const QString& language) = 0;
};
