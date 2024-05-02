#include "UserLettersDelegate.hpp"

#include <optional>

#include <QPainter>

Q_DECLARE_METATYPE(std::optional<ScrabbleLetter>)

UserLettersDelegate::UserLettersDelegate(std::shared_ptr<ITextureHandler> textureHandeler, QObject* parent)
    :QStyledItemDelegate(parent), textureHandeler_(textureHandeler) { }

void UserLettersDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QPixmap letter = {};
    auto tile = index.data().value<std::optional<ScrabbleLetter>>();

    if (!tile)
        letter = textureHandeler_->getTileTexture(ITextureHandler::FieldTextureType::TRANSPARMENT);
    else if (tile->type == ScrabbleLetter::Type::NORMAL_TILE)
        letter = textureHandeler_->getLetterTexture(tile->letter, option.rect.size().width());
    else
        letter = textureHandeler_->getTileTexture(ITextureHandler::FieldTextureType::EMPTY_TILE);

    painter->drawPixmap(option.rect, letter);
}

QSize UserLettersDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(59, 59);
}
