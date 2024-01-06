#pragma once

#include "ILanguagesHandler.hpp"

class LanguageHandler: public ILanguagesHandler
{
public:
    static constexpr inline char LANGUAGE_PATH[] = "/Resources/Languages/";
    static constexpr inline char WORDS_FILE_LOCAL_PATH[] = "/words.txt";
    static constexpr inline char LETTERS_INFO_FILE_LOCAL_PATH[] = "/letters_info.txt";

    std::vector<QString> getAvailableLanguages() override;
    QString getWordsFilePath(const QString& language) override;
    QString getLettersInfoFilePath(const QString& language) override;

private:
    static constexpr inline char ERROR_HINT[] = "make sure that the executable file is in the same folder as the \"Resources\""
                                                " folder and that the contents of the \"Resources\" folder have not been changed";
};
