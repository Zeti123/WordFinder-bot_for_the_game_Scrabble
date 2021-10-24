#include "TableViewBasedGameBoard.hpp"

#include <QItemSelectionModel>

TableViewBasedGameBoard::TableViewBasedGameBoard(QTableView& tableView)
    :tableView_(tableView), gameBoard_({}), viewdGameBoard_({}), current_({})
{
    auto selectionModel = tableView_.selectionModel();
    connect(selectionModel, &QItemSelectionModel::currentChanged, this, &TableViewBasedGameBoard::getCurrentChange);
}

Q_DECLARE_METATYPE(GameBoardTile)
void TableViewBasedGameBoard::updateGameBoard(const GameBoard& gameBoard)
{
    gameBoard_ = gameBoard;
    updateDisplay(gameBoard_);
    emit IGameBoardDisplay::gameBoardChanged(gameBoard_);
}

void TableViewBasedGameBoard::showResultView(const WordPlacement& result)
{
    auto copy = gameBoard_;
    copy.putWord(result);
    updateDisplay(copy);
}

void TableViewBasedGameBoard::hideResultView()
{
    updateGameBoard(gameBoard_);
}

void TableViewBasedGameBoard::updateDisplay(const GameBoard& gameBoard)
{
    viewdGameBoard_ = gameBoard;
    for (std::size_t i = 0; i < GameBoard::size; i++)
    {
        for (std::size_t j = 0; j < GameBoard::size; j++)
        {
            tableView_.model()->setData(tableView_.model()->index(i, j), QVariant::fromValue<GameBoardTile>(gameBoard[i][j]), Qt::EditRole);
            setBackgroundColor(tableView_.model()->index(i, j), gameBoard_[i][j], viewdGameBoard_[i][j]);
        }
    }
    tableView_.model()->setData({}, {}, Qt::DisplayRole);
}

void TableViewBasedGameBoard::setBackgroundColor(const QModelIndex& modelIndex, const GameBoardTile& currentGameBoardTile, const GameBoardTile& gameBoardTileToDisplay)
{
    if (gameBoardTileToDisplay.valueType == GameBoardTile::ValueType::EMPTY)
    {
        tableView_.model()->setData(modelIndex, QVariant::fromValue('t'), Qt::BackgroundRole);
        return;
    }

    char color = 't';
    if (currentGameBoardTile.valueType == GameBoardTile::ValueType::EMPTY)
        color = 'g';
    else if (!(currentGameBoardTile == gameBoardTileToDisplay))
        color = 'r';

    tableView_.model()->setData(modelIndex, QVariant::fromValue(color), Qt::BackgroundRole);
}

const GameBoard& TableViewBasedGameBoard::getGameBoard()
{
    return gameBoard_;
}

const GameBoard& TableViewBasedGameBoard::getViewdGameBoard()
{
    return viewdGameBoard_;
}

std::pair<uint8_t, uint8_t> TableViewBasedGameBoard::getSelectedFiled()
{
    return current_;
}

void TableViewBasedGameBoard::getCurrentChange(const QModelIndex &current, const QModelIndex&)
{
    current_ = std::make_pair(current.column(), current.row());
    emit selectionChanged(std::make_pair(current.column(), current.row()));
}
