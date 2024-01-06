#include "FileReadHelpers.hpp"
#include "LanguageInfo.hpp"

LettersInfo getLettersInfo(const LanguageInfo& languageInfo, std::shared_ptr<ILettersRenumberer> renumberer)
{
    std::vector<std::pair<char, std::size_t>> letters;

    for (auto letter: languageInfo.lettersInfo)
        letters.push_back(std::make_pair(renumberer->getNumFromLetter(letter.first.unicode()), letter.second));

    return LettersInfo(letters);
}

std::vector<char32_t> getAllLetters(const LanguageInfo& languageInfo)
{
    std::vector<char32_t> allLetters;

    for (auto& [letter, _]: languageInfo.lettersInfo)
        allLetters.push_back(letter.unicode());

    return allLetters;

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
