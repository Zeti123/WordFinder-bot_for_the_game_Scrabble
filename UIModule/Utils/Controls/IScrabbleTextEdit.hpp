#ifndef ITEXTEDIT_HPP
#define ITEXTEDIT_HPP

#include "ScrabbleString.hpp"

#include <QObject>

class IScrabbleTextEdit: public QObject
{
    Q_OBJECT

public:
    virtual ~IScrabbleTextEdit() = default;
    virtual void setText(const ScrabbleString& text) = 0;
    virtual ScrabbleString getText() = 0;

signals:
    void textChanged(const ScrabbleString& text);
};

#endif // ITEXTEDIT_HPP
