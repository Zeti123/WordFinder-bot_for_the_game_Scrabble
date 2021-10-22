#ifndef ILANGUAGESHANDELER_HPP
#define ILANGUAGESHANDELER_HPP

#include <QString>
#include <vector>

class ILanguagesHandeler
{
public:
    virtual ~ILanguagesHandeler() = default;
    virtual std::vector<QString> getAvailableLanguages() = 0;
    virtual QString getWordsFilePath(const QString& language) = 0;
    virtual QString getLettersInfoFilePath(const QString& language) = 0;
};

#endif // ILANGUAGESHANDELER_HPP
