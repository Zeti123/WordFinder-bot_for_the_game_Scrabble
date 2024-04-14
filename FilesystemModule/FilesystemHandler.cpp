#include "FilesystemHandler.hpp"

#include <memory>

FilesystemHandler::FilesystemHandler(std::unique_ptr<ILanguagesHandler>&& languageHandler, std::unique_ptr<IFileReader>&& fileReader)
    :languageHandler_(std::move(languageHandler)), fileReader_(std::move(fileReader)) { }

std::vector<QString> FilesystemHandler::getAvailableLanguages()
{
    return languageHandler_->getAvailableLanguages();
}

LanguageInfo FilesystemHandler::getLanguageInfo(const QString& language)
{
    const auto wordsFilePath = languageHandler_->getWordsFilePath(language);
    const auto lettersInfoFilePath = languageHandler_->getLettersInfoFilePath(language);

    auto listOfWords = fileReader_->readWordsFile(wordsFilePath);
    auto lettersInfo = fileReader_->readLettersInfoFile(lettersInfoFilePath);

    return LanguageInfo {std::move(listOfWords), std::move(lettersInfo)};
}
