#include "ListItemDelegate.hpp"

#include <QPainter>

ListItemDelegate::ListItemDelegate(QObject* parent)
    :QStyledItemDelegate (parent){}

void ListItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const{
    if(option.state & QStyle::State_Selected)
    {
        //painter->fillRect(option.rect, option.palette.color(QPalette::Highlight));
        painter->fillRect(option.rect, QColor(100, 100, 100, 120));
    }

    QString title = index.data(Qt::DisplayRole).toString();
    QString description = index.data(Qt::UserRole + 1).toString();

    auto r = option.rect.adjusted(10, 0, 0, -20);
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom|Qt::AlignLeft|Qt::TextWordWrap, title, &r);
    painter->fillRect(QRect(QPoint(205, option.rect.y() + 2), QPoint(207, option.rect.y() + option.rect.height() - 4)), QColor(0, 0, 0, 255));


    QFont font = painter->font();
    QFont tmp = font;
    font.setPointSize(12);
    painter->setFont(font);
    r = option.rect.adjusted(215, 10, 0, 0);
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft|Qt::TextWordWrap, description + " pkt", &r);
    painter->setFont(tmp);
}

QSize ListItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const{
    return QSize(200, 50);
}
