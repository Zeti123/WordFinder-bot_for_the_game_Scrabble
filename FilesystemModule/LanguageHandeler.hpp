#ifndef LANGUAGEHANDELER_HPP
#define LANGUAGEHANDELER_HPP

#include "ILanguagesHandeler.hpp"

class LanguageHandeler: public ILanguagesHandeler
{
public:
    std::vector<QString> getAvailableLanguages() override;
    QString getWordsFilePath(const QString& language) override;
    QString getLettersInfoFilePath(const QString& language) override;

private:
    constexpr static char ERROR_HINT[] = "make sure that the executable file is in the same folder as the \"Src\""
                                         " folder and that the contents of the \"Src\" folder have not been changed";
};

#endif // LANGUAGEHANDELER_HPP
