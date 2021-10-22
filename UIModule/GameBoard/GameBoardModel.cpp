#include "GameBoardModel.hpp"

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

QVariant GameBoardModel::headerData(int section, Qt::Orientation orientation, int) const
{
    if (orientation == Qt::Orientation::Horizontal)
        return QString::number(section);
    return QString(QChar('a' + section));
}

QVariant GameBoardModel::data(const QModelIndex& index, int) const
{
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
    else if (role == Qt::DisplayRole)
    {
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}
