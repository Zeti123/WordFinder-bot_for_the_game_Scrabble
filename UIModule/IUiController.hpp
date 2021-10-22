#ifndef IGAMEBOARDCONTROLLER_HPP
#define IGAMEBOARDCONTROLLER_HPP

#include "ScrabbleString.hpp"
#include "IGameBoardDisplay.hpp"
#include "IUserLettersDisplay.hpp"

#include "AlgorithmModule/ScrabbleSearchEngineResult.hpp"

#include <memory>

#include <QObject>

class GameBoard;
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
    virtual void updateResults(const std::vector<ScrabbleSearchEngineResult>& results) = 0;
    virtual void updateResults(std::vector<ScrabbleSearchEngineResult>&& results) = 0;

signals:
    void gameStateChanged(const GameState& gameState);
};

#endif // IGAMEBOARDCONTROLLER_HPP
