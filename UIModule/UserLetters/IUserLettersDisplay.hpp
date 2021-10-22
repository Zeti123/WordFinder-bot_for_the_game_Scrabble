#ifndef IUSERLETTERSDISPLAY_HPP
#define IUSERLETTERSDISPLAY_HPP

#include "ScrabbleString.hpp"

#include <optional>
#include <QObject>
#include <array>

class IUserLettersDisplay: public QObject
{
    Q_OBJECT

public:
    static constexpr uint8_t UserLettersNum = 7;
    using DataType = std::array<std::optional<ScrabbleLetter>, UserLettersNum>;

    virtual ~IUserLettersDisplay() = default;
    virtual void setUserLetters(const DataType& userLetters) = 0;
    virtual void showUserLettersView(const DataType& userLetters) = 0;
    virtual void hideUserLettersView() = 0;
    virtual DataType getUserLetters() = 0;
    virtual DataType getViewdUserLetters() = 0;

signals:
    void userLettersChanged(const DataType& userLetters);
};

#endif // IUSERLETTERSDISPLAY_HPP
