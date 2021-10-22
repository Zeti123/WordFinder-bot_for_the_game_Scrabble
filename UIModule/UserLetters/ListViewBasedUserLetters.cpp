#include "ListViewBasedUserLetters.hpp"

Q_DECLARE_METATYPE(std::optional<ScrabbleLetter>)
ListViewBasedUserLetters::ListViewBasedUserLetters(QTableView& listView)
    :listView_(listView) { }

void ListViewBasedUserLetters::setUserLetters(const DataType& userLetters)
{
    userLetters_ = userLetters;
    show(userLetters);
    emit userLettersChanged(userLetters);
}

void ListViewBasedUserLetters::showUserLettersView(const IUserLettersDisplay::DataType& userLetters)
{
    viewdUserLetters_ = userLetters;
    show(userLetters);
}

void ListViewBasedUserLetters::hideUserLettersView()
{
    viewdUserLetters_ = userLetters_;
    show(userLetters_);
}

IUserLettersDisplay::DataType ListViewBasedUserLetters::getViewdUserLetters()
{
    return viewdUserLetters_;
}


ListViewBasedUserLetters::DataType ListViewBasedUserLetters::getUserLetters()
{
    return userLetters_;
}

void ListViewBasedUserLetters::show(const IUserLettersDisplay::DataType& userLetters)
{
    auto& model = *listView_.model();
    for (std::size_t i = 0; i < 7; i++)
    {
        model.setData(model.index(0, i), QVariant::fromValue<std::optional<ScrabbleLetter>>(userLetters[i]), Qt::EditRole);
    }
    listView_.model()->setData({}, {}, Qt::DisplayRole);
}
