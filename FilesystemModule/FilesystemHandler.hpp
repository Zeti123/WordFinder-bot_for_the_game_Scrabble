#pragma once

#include "IFilesystemHandler.hpp"

#include <memory>

#include "IFileReader.hpp"
#include "ILanguagesHandler.hpp"

class FilesystemHandler: public IFilesystemHandler
{
public:
    FilesystemHandler(std::unique_ptr<ILanguagesHandler>&& languageHandler, std::unique_ptr<IFileReader>&& fileReader);

    std::vector<QString> getAvailableLanguages() override;
    LanguageInfo getLanguageInfo(const QString& language) override;

private:
    std::unique_ptr<ILanguagesHandler> languageHandler_;
    std::unique_ptr<IFileReader> fileReader_;
};
