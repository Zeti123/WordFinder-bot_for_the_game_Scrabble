#ifndef GAMEBOARDDELEGATE_HPP
#define GAMEBOARDDELEGATE_HPP

#include "GameBoard.hpp"
#include "ITextureHandler.hpp"

#include <memory>

#include <QObject>
#include <QStyledItemDelegate>
#include <QPainter>

class GameBoardDelegate : public QStyledItemDelegate
{
public:
    GameBoardDelegate(std::shared_ptr<ITextureHandler> textureHandeler, QObject *parent = nullptr);
    void paint (QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;
    QSize sizeHint (const QStyleOptionViewItem & option, const QModelIndex & index) const override;

private:
    std::shared_ptr<ITextureHandler> textureHandeler_;
};
#endif // GAMEBOARDDELEGATE_HPP
