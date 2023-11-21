#ifndef LANGUAGEHANDLER_H
#define LANGUAGEHANDLER_H

#include "ILanguagesHandler.hpp"

class LanguageHandler: public ILanguagesHandler
{
public:
    std::vector<QString> getAvailableLanguages() override;
    QString getWordsFilePath(const QString& language) override;
    QString getLettersInfoFilePath(const QString& language) override;

private:
    constexpr static char ERROR_HINT[] = "make sure that the executable file is in the same folder as the \"Resources\""
                                         " folder and that the contents of the \"Resources\" folder have not been changed";
};

#endif // LANGUAGEHANDLER_H
