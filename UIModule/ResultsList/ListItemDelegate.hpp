#ifndef LISTITEMDELEGATE_HPP
#define LISTITEMDELEGATE_HPP

#include <QStyledItemDelegate>

class ListItemDelegate : public QStyledItemDelegate
{
public:
    ListItemDelegate(QObject *parent = nullptr);
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};

#endif // LISTITEMDELEGATE_HPP
