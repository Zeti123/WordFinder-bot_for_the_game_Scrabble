#include "GameBoardModel.hpp"

#include <QColor>
#include <QChar>

GameBoardModel::GameBoardModel(const GameBoard& gameBoard)
    : gameBoard_(gameBoard) { }

int GameBoardModel::rowCount(const QModelIndex&) const
{
    return GameBoard::size;
}

int GameBoardModel::columnCount(const QModelIndex&) const
{
    return GameBoard::size;
}

QVariant GameBoardModel::headerData(int, Qt::Orientation, int) const
{
    return QString("");
}

QVariant GameBoardModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::BackgroundRole)
        return QVariant::fromValue(backgroundColor_[index.row()][index.column()]);

    return QVariant::fromValue(gameBoard_[index.row()][index.column()]);
}

Qt::ItemFlags GameBoardModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool GameBoardModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        gameBoard_[index.row()][index.column()] = qvariant_cast<GameBoardTile>(value);
        return true;
    }
    else if (role == Qt::BackgroundRole)
    {
        backgroundColor_[index.row()][index.column()] = qvariant_cast<char>(value);
        return true;
    }
    else if (role == Qt::DisplayRole)
    {
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}
