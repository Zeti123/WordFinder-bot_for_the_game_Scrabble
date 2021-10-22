#include "LineTextScrabbleTextEdit.hpp"

LineTextScrabbleTextEdit::LineTextScrabbleTextEdit(QLineEdit& lineEdit, std::shared_ptr<ILettersRenumberer> renumberer, bool noInfoEmptyTileMode)
    :lineEdit_(lineEdit), renumberer_(renumberer), noInfoEmptyTileMode_(noInfoEmptyTileMode)
{
    connect(&lineEdit, &QLineEdit::textChanged, this, &LineTextScrabbleTextEdit::receiveTextChange);
}

void LineTextScrabbleTextEdit::setText(const ScrabbleString& text)
{
    lineEdit_.setText(scrabbleStringtoQString(text));
}

ScrabbleString LineTextScrabbleTextEdit::getText()
{
    return qStringToScrabbleString(lineEdit_.text());
}

void LineTextScrabbleTextEdit::receiveTextChange(const QString& text)
{
    emit textChanged(qStringToScrabbleString(text));
}

ScrabbleString LineTextScrabbleTextEdit::qStringToScrabbleString(const QString& str) const
{
    ScrabbleString s;
    s.reserve(str.size());
    for (int i = 0; i < str.size(); i++)
    {
        wchar_t letter = str[i].unicode();
        if (!(renumberer_->isLetterValid(letter) || letter == '?'))
            return {};

        if (letter == '?' && noInfoEmptyTileMode_)
            s.push_back(ScrabbleLetter('\0', ScrabbleLetter::Type::EMPTY_TILE));
        else if (letter == '?' && i + 1 < str.size() && renumberer_->isLetterValid(str[i+1].unicode()))
        {
            s.push_back(ScrabbleLetter(renumberer_->getNumFromLetter(str[i+1].unicode()), ScrabbleLetter::Type::EMPTY_TILE));
            i++;
        }
        else if (letter != '?')
            s.push_back(ScrabbleLetter(renumberer_->getNumFromLetter(letter), ScrabbleLetter::Type::NORMAL_TILE));
    }
    return s;
}

QString LineTextScrabbleTextEdit::scrabbleStringtoQString(const ScrabbleString& str) const
{
    QString s;
    s.reserve(str.size());
    for (auto letter: str)
    {
        if (letter.type == ScrabbleLetter::Type::EMPTY_TILE)
            s.push_back(QString('?') + letter.letter);
        else
            s.push_back(QChar(letter.letter));
    }
    return s;
}
