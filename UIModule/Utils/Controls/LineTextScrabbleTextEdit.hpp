#ifndef QLINETEXTSCRABBLETEXTEDIT_HPP
#define QLINETEXTSCRABBLETEXTEDIT_HPP

#include "IScrabbleTextEdit.hpp"
#include "ILettersRenumberer.hpp"

#include <memory>

#include <QLineEdit>

class LineTextScrabbleTextEdit: public IScrabbleTextEdit
{
    Q_OBJECT

public:
    LineTextScrabbleTextEdit(QLineEdit& lineEdit, std::shared_ptr<ILettersRenumberer> renumberer, bool noInfoEmptyTileMode = false);
    void setText(const ScrabbleString& text) override;
    ScrabbleString getText() override;

private slots:
    void receiveTextChange(const QString& text);

private:
    ScrabbleString qStringToScrabbleString(const QString& str) const;
    QString scrabbleStringtoQString(const ScrabbleString& str) const;
    QLineEdit& lineEdit_;
    std::shared_ptr<ILettersRenumberer> renumberer_;
    bool noInfoEmptyTileMode_;
};

#endif // QLINETEXTSCRABBLETEXTEDIT_HPP
