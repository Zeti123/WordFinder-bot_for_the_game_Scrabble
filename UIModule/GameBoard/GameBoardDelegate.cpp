#include "GameBoardDelegate.hpp"

Q_DECLARE_METATYPE(GameBoardTile)

GameBoardDelegate::GameBoardDelegate(std::shared_ptr<ITextureHandeler> textureHandeler, QObject* parent)
    : QStyledItemDelegate(parent), textureHandeler_(textureHandeler) { }

void GameBoardDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QPixmap* background = nullptr;
    QPixmap letter = {};
    GameBoardTile tile = index.data().value<GameBoardTile>();

    if (tile.valueType == GameBoardTile::ValueType::NORMAL_TILE)
        letter = textureHandeler_->getLetterTexture(tile.value);
    else if (tile.valueType == GameBoardTile::ValueType::EMPTY_TILE)
        letter = textureHandeler_->getEmptyTileForLetter(tile.value);
    else
        letter = textureHandeler_->getTileTexture(ITextureHandeler::FieldTextureType::TRANSPARMENT);

    switch (GameBoard::getFieldBonus(index.row(), index.column()))
    {
    case FieldBonus::NONE:
        background = &textureHandeler_->getTileTexture(ITextureHandeler::FieldTextureType::NORMAL); break;
    case FieldBonus::LETTERX2:
        background = &textureHandeler_->getTileTexture(ITextureHandeler::FieldTextureType::LETTERX2); break;
    case FieldBonus::LETTERX3:
        background = &textureHandeler_->getTileTexture(ITextureHandeler::FieldTextureType::LETTERX3); break;
    case FieldBonus::WORDX2:
        background = &textureHandeler_->getTileTexture(ITextureHandeler::FieldTextureType::WORDX2); break;
    case FieldBonus::WORDX3:
        background = &textureHandeler_->getTileTexture(ITextureHandeler::FieldTextureType::WORDX3); break;
    }


    painter->drawPixmap(option.rect, *background);
    painter->drawPixmap(option.rect, letter);

    if(option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, QColor(100, 100, 100, 120));
}

QSize GameBoardDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const
{
    return QSize(58, 58);
}
