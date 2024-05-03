#pragma once

#include "IUserLettersDisplay.hpp"

#include <QObject>

#include "AlgorithmModule/ScrabbleSearchEngineResult.hpp"
#include "GameBoard.hpp"

struct WordPlacement;
enum class Orientation;

struct GameState
{
    GameBoard gameBoard;
    IUserLettersDisplay::DataType userLetters;
};

class IUiController: public QObject
{
    Q_OBJECT

public:
    virtual ~IUiController() = default;
    virtual void updateResults(std::vector<ScrabbleSearchEngineResult>&& results) = 0;

signals:
    void gameStateChanged(const GameState& gameState);
};
