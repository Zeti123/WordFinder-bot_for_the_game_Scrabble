#ifndef USERLETTERSDELEGATE_HPP
#define USERLETTERSDELEGATE_HPP

#include "ITextureHandeler.hpp"
#include "ILettersRenumberer.hpp"
#include "ScrabbleString.hpp"

#include <memory>

#include <QStyledItemDelegate>

class UserLettersDelegate : public QStyledItemDelegate
{
public:
    UserLettersDelegate(std::shared_ptr<ITextureHandeler> textureHandeler, QObject* parent = nullptr);
    void paint(QPainter * painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
    std::shared_ptr<ITextureHandeler> textureHandeler_;
};

#endif // USERLETTERSDELEGATE_HPP
