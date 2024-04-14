#include "FileReader.hpp"

#include <stdexcept>

#include <QFile>
#include <QTextStream>
#include <QString>

std::vector<QString> FileReader::readWordsFile(const QString& filename)
{
    std::vector<QString> words;
    QString fileString = readToString(filename);
    auto stream = QTextStream(&fileString);
    while (true)
    {
        QString str;
        stream >> str;

        if (stream.status() != QTextStream::Status::Ok)
            break;

        words.push_back(str);
    }
    return words;
}

std::vector<std::pair<QChar, std::size_t> > FileReader::readLettersInfoFile(const QString& filename)
{
    std::vector<std::pair<QChar, std::size_t>> letters;
    QString fileString = readToString(filename);
    auto stream = QTextStream(&fileString);
    while (true)
    {
        QString str;
        std::size_t p;
        stream >> str >> p;

        if (stream.status() != QTextStream::Status::Ok)
            break;

        letters.push_back(std::make_pair(str[0], p));
    }

    return letters;
}

QString FileReader::readToString(const QString& filename)
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
        std::runtime_error("cannot open file: " + filename.toStdString());

    QTextStream fileStream(&file);
    QString fileString = fileStream.readAll();
    file.close();
    return fileString;
}
