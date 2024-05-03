#include "ListItemDelegate.hpp"

#include <QPainter>

#include "ScrabbleSearchEngineResult.hpp"

Q_DECLARE_METATYPE(ScrabbleSearchEngineResult)

ListItemDelegate::ListItemDelegate(QObject* parent, const std::shared_ptr<ILettersRenumberer> lettersRenumberer)
    :QStyledItemDelegate (parent), renumberer_(lettersRenumberer) {}

void ListItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const{
    if(option.state & QStyle::State_Selected)
    {
        painter->fillRect(option.rect, QColor(100, 100, 100, 120));
    }

    auto [word, points] = index.data().value<ScrabbleSearchEngineResult>();
    auto readableWord = QString::fromStdWString(convertToReadable(word.word));
    auto pointsStr = QString::number(points);

    auto r = option.rect.adjusted(10, 0, 0, -20);
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom|Qt::AlignLeft|Qt::TextWordWrap, readableWord, &r);
    painter->fillRect(QRect(QPoint(205, option.rect.y() + 2), QPoint(207, option.rect.y() + option.rect.height() - 4)), QColor(0, 0, 0, 255));


    QFont font = painter->font();
    QFont tmp = font;
    font.setPointSize(12);
    painter->setFont(font);
    r = option.rect.adjusted(215, 10, 0, 0);
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft|Qt::TextWordWrap, pointsStr + " pkt", &r);
    painter->setFont(tmp);
}

QSize ListItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const{
    return QSize(200, 50);
}

std::wstring ListItemDelegate::convertToReadable(const ScrabbleString& str) const
{
    std::wstring ret;
    ret.reserve(str.size());
    for (auto letter: str)
    {
        ret.push_back(renumberer_->getLetterFromNum(letter.letter));
    }
    return ret;
}
