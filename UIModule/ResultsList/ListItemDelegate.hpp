#pragma once

#include <QStyledItemDelegate>

#include "ScrabbleString.hpp"
#include "ILettersRenumberer.hpp"

class ListItemDelegate : public QStyledItemDelegate
{
public:
    ListItemDelegate(QObject *parent = nullptr, const std::shared_ptr<ILettersRenumberer> lettersRenumberer = nullptr);
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;

private:
    std::wstring convertToReadable(const ScrabbleString& str) const;

    std::shared_ptr<ILettersRenumberer> renumberer_;
};
