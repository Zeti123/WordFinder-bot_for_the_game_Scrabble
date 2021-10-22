#ifndef LISTVIEWBASEDUSERLETTERS_HPP
#define LISTVIEWBASEDUSERLETTERS_HPP

#include "IUserLettersDisplay.hpp"

#include <QTableView>

class ListViewBasedUserLetters: public IUserLettersDisplay
{
public:
    ListViewBasedUserLetters(QTableView& listView);
    void setUserLetters(const DataType& userLetters) override;
    void showUserLettersView(const DataType& userLetters) override;
    void hideUserLettersView() override;
    DataType getViewdUserLetters() override;
    DataType getUserLetters() override;

private:
    void show(const DataType& userLetters);
    QTableView& listView_;
    DataType userLetters_;
    DataType viewdUserLetters_;
};

#endif // LISTVIEWBASEDUSERLETTERS_HPP
