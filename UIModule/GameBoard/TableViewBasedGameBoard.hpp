#ifndef TABLEVIEWBASEDGAMEBOARD_HPP
#define TABLEVIEWBASEDGAMEBOARD_HPP

#include "IGameBoardDisplay.hpp"
#include "IUiController.hpp"

#include <QTableView>

class TableViewBasedGameBoard: public IGameBoardDisplay
{
    Q_OBJECT

public:
    TableViewBasedGameBoard(QTableView& tableView);
    void updateGameBoard(const GameBoard& gameBoard) override;
    void showResultView(const WordPlacement& result) override;
    void hideResultView() override;
    const GameBoard& getGameBoard() override;
    const GameBoard& getViewdGameBoard() override;
    std::pair<uint8_t, uint8_t> getSelectedFiled() override;

private:
    void updateDisplay(const GameBoard& gameBoard);
    void setBackgroundColor(const QModelIndex& modelIndex, const GameBoardTile& currentGameBoardTile, const GameBoardTile& gameBoardTileToDisplay);
    QTableView& tableView_;
    GameBoard gameBoard_;
    GameBoard viewdGameBoard_;
    std::pair<uint8_t, uint8_t> current_;

private slots:
    void getCurrentChange(const QModelIndex &current, const QModelIndex &previous);
};

#endif // TABLEVIEWBASEDGAMEBOARD_HPP
