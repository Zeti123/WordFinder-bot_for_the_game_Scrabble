#include "GameBoardDelegate.hpp"

#include <QChar>

Q_DECLARE_METATYPE(GameBoardTile)

GameBoardDelegate::GameBoardDelegate(std::shared_ptr<ITextureHandler> textureHandeler, QObject* parent)
    : QStyledItemDelegate(parent), textureHandeler_(textureHandeler) { }

void GameBoardDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QPixmap* background = nullptr;
    QPixmap letter = {};
    GameBoardTile tile = index.data().value<GameBoardTile>();
    char color = index.data(Qt::BackgroundRole).value<char>();

    if (tile.valueType == GameBoardTile::ValueType::NORMAL_TILE)
        letter = textureHandeler_->getLetterTexture(tile.value, option.rect.size().width());
    else if (tile.valueType == GameBoardTile::ValueType::EMPTY_TILE)
        letter = textureHandeler_->getEmptyTileForLetter(tile.value, option.rect.size().width());
    else
        letter = textureHandeler_->getTileTexture(ITextureHandler::FieldTextureType::TRANSPARMENT);

    switch (GameBoard::getFieldBonus(index.row(), index.column()))
    {
    case FieldBonus::NONE:
        background = &textureHandeler_->getTileTexture(ITextureHandler::FieldTextureType::NORMAL); break;
    case FieldBonus::LETTERX2:
        background = &textureHandeler_->getTileTexture(ITextureHandler::FieldTextureType::LETTERX2); break;
    case FieldBonus::LETTERX3:
        background = &textureHandeler_->getTileTexture(ITextureHandler::FieldTextureType::LETTERX3); break;
    case FieldBonus::WORDX2:
        background = &textureHandeler_->getTileTexture(ITextureHandler::FieldTextureType::WORDX2); break;
    case FieldBonus::WORDX3:
        background = &textureHandeler_->getTileTexture(ITextureHandler::FieldTextureType::WORDX3); break;
    }

    painter->drawPixmap(option.rect, *background);
    painter->drawPixmap(option.rect, letter);
    QColor bgColor;
    switch (color)
    {
    case 'g':
        bgColor = QColor(0, 180, 0, 70); break;
    case 'r':
        bgColor = QColor(180, 0, 0, 70); break;
    case 't':
    default:
        bgColor = QColor(0, 0, 0, 0);
    }

    painter->fillRect(option.rect, bgColor);
    if(option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, QColor(100, 100, 100, 120));
}

QSize GameBoardDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const
{
    return QSize(58, 58);
}
