#include "LanguageHandeler.hpp"

#include <algorithm>
#include <filesystem>

std::vector<QString> LanguageHandeler::getAvailableLanguages()
{
    namespace fs = std::filesystem;
    auto currentPath = fs::current_path();
    currentPath += "/Src/Languages/";

    if (!fs::exists(currentPath))
        throw std::runtime_error(std::string("cannot find ./Src/Languages folder\n") + ERROR_HINT);

    std::vector<QString> languages;
    for (auto file: fs::directory_iterator(currentPath))
    {
        if (!fs::is_directory(file))
            continue;

        auto folderName = file.path().filename().string();
        languages.push_back(QString::fromStdString(folderName));
    }
    std::sort(languages.begin(), languages.end());
    return languages;
}

QString LanguageHandeler::getWordsFilePath(const QString& language)
{
    namespace fs = std::filesystem;
    auto path = fs::current_path();
    path += "/Src/Languages/" + language.toStdString() + "/words.txt";
    if (!fs::exists(path))
        throw std::runtime_error("cannot find" + path.string() + " file\n" + ERROR_HINT);

    return QString::fromStdString(path);
}

QString LanguageHandeler::getLettersInfoFilePath(const QString& language)
{
    namespace fs = std::filesystem;
    auto path = fs::current_path();
    path += "/Src/Languages/" + language.toStdString() + "/letters_info.txt";
    if (!fs::exists(path))
        throw std::runtime_error("cannot find" + path.string() + " file\n" + ERROR_HINT);

    return QString::fromStdString(path);
}
