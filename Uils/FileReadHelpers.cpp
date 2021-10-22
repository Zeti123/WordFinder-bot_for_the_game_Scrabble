#include "FileReadHelpers.hpp"

LettersInfo getLettersInfo(const std::string& filename, std::shared_ptr<ILettersRenumberer> renumberer)
{
    std::vector<std::pair<char, std::size_t>> letters;
    FileReader reader;
    auto loadedLetters = reader.readLettersInfoFile(QString::fromStdString(filename));
    for (auto letter: loadedLetters)
        letters.push_back(std::make_pair(renumberer->getNumFromLetter(letter.first.unicode()), letter.second));
    return LettersInfo(letters);
}

std::vector<wchar_t> readFile(const std::string& filename)
{
    std::vector<wchar_t> ret;
    FileReader reader;
    auto letters = reader.readLettersInfoFile(QString::fromStdString(filename));
    for (auto letter: letters)
        ret.push_back(letter.first.unicode());
    return ret;

}

std::vector<std::string> convertFromQStringVector(const std::vector<QString>& words, std::shared_ptr<ILettersRenumberer> renumberer)
{
    std::vector<std::string> converted = {};
    converted.reserve(words.size());
    for (const auto& word: words)
    {
        std::string convertedWord;
        convertedWord.reserve(word.size());
        for (auto letter: word)
            convertedWord.push_back(renumberer->getNumFromLetter(letter.unicode()));
        converted.push_back(convertedWord);
    }
    return converted;
}
