#ifndef IGAMEBOARDDISPLAY_HPP
#define IGAMEBOARDDISPLAY_HPP

#include "GameBoard.hpp"

#include <QObject>

class IGameBoardDisplay: public QObject
{
Q_OBJECT

public:
    virtual void updateGameBoard(const GameBoard& gameBoard) = 0;
    virtual void showResultView(const WordPlacement& result) = 0;
    virtual void hideResultView() = 0;
    virtual const GameBoard& getGameBoard() = 0;
    virtual const GameBoard& getViewdGameBoard() = 0;
    virtual std::pair<uint8_t, uint8_t> getSelectedFiled() = 0;

signals:
    void selectionChanged(std::pair<uint8_t, uint8_t> position);
    void gameBoardChanged(const GameBoard& newGameBoard);
};



#endif // IGAMEBOARDDISPLAY_HPP
