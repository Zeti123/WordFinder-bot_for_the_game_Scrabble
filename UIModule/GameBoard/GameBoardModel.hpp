#ifndef GAMEBOARDMODEL_HPP
#define GAMEBOARDMODEL_HPP

#include "GameBoard.hpp"

#include <QAbstractTableModel>

Q_DECLARE_METATYPE(GameBoardTile)
class GameBoardModel: public QAbstractTableModel
{
public:
    GameBoardModel(const GameBoard& gameBoard);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    GameBoard gameBoard_;
};

#endif // GAMEBOARDMODEL_HPP
