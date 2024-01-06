#include "LanguageHandler.hpp"

#include <algorithm>
#include <filesystem>

std::vector<QString> LanguageHandler::getAvailableLanguages()
{
    namespace fs = std::filesystem;
    const auto currentPath = std::string(fs::current_path());
    const auto languagePath = currentPath + LANGUAGE_PATH;

    if (!fs::exists(currentPath))
        throw std::runtime_error(std::string("cannot find ") + LANGUAGE_PATH + " folder in " + currentPath + " " + ERROR_HINT);

    std::vector<QString> languages;
    for (const auto& file: fs::directory_iterator(languagePath))
    {
        if (!fs::is_directory(file))
            continue;

        auto folderName = file.path().filename().string();
        languages.push_back(QString::fromStdString(folderName));
    }
    std::sort(languages.begin(), languages.end());
    return languages;
}

QString LanguageHandler::getWordsFilePath(const QString& language)
{
    namespace fs = std::filesystem;
    const auto wordsPath = std::string(fs::current_path()) + LANGUAGE_PATH + language.toStdString() + WORDS_FILE_LOCAL_PATH;
    if (!fs::exists(wordsPath))
        throw std::runtime_error("cannot find" + wordsPath + " file\n" + ERROR_HINT);

    return QString::fromStdString(wordsPath);
}

QString LanguageHandler::getLettersInfoFilePath(const QString& language)
{
    namespace fs = std::filesystem;
    const auto lettersInfoPath = std::string(fs::current_path()) + LANGUAGE_PATH + language.toStdString() + LETTERS_INFO_FILE_LOCAL_PATH;
    if (!fs::exists(lettersInfoPath))
        throw std::runtime_error("cannot find" + lettersInfoPath + " file\n" + ERROR_HINT);

    return QString::fromStdString(lettersInfoPath);
}
