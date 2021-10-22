#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include "IFileReader.hpp"

#include <QString>

class FileReader: public IFileReader
{
public:
    std::vector<QString> readWordsFile(const QString& filename) override;
    std::vector<std::pair<QChar, std::size_t> > readLettersInfoFile(const QString& filename) override;

private:
    QString readToString(const QString& filename);
};

#endif // FILEREADER_HPP
