#include "GameBoardHelpers.hpp"

#include "log.hpp"

GameBoard reflectGameBoard(const GameBoard& gameBoard)
{
    logger::debug("GameBoardHelpers::reflectGameBoard(", gameBoard, ")\n");

    GameBoard reflectedGameBoard;
    for (size_t i = 0; i < GameBoard::size; i++)
        for (size_t j = 0; j < GameBoard::size; j++)
            reflectedGameBoard[i][j] = gameBoard[j][i];

    return reflectedGameBoard;
}

WordPlacement findWordVerticallyCrossedBy(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position)
{
    logger::debug("GameBoardHelpers::findWordVerticallyCrossedBy(", static_cast<std::pair<std::size_t, std::size_t>>(position), ")\n");
    ScrabbleString prefix = findPrefixForPos(gameBoard, position);
    ScrabbleString sufix = findSufixForPos(gameBoard, position);
    ScrabbleString str = prefix + gameBoard[position.second][position.first].toScrabbleLetter() + sufix;
    auto resultPosition = std::make_pair(position.first, position.second - prefix.size());
    Orientation orientation = Orientation::VERTICAL;
    return WordPlacement(str, resultPosition, orientation);
}

WordPlacement findWordHorizontallyCrossedBy(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position)
{
    logger::debug("GameBoardHelpers::findWordHorizontallyCrossedBy(", static_cast<std::pair<std::size_t, std::size_t>>(position), ")\n");
    GameBoard reflectedGameBoard = reflectGameBoard(gameBoard);
    auto placement = findWordVerticallyCrossedBy(reflectedGameBoard, std::make_pair(position.second, position.first));
    placement.orientation = Orientation::HORIZONTAL;
    std::swap(placement.position.second, placement.position.first);
    return placement;
}

ScrabbleString findPrefixForPos(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position)
{
    logger::debug("GameBoardHelpers::findPrefixForPos(", gameBoard, static_cast<std::size_t>(position.first), ' ',
                 static_cast<std::size_t>(position.second), ")\n");

    ScrabbleString res;
    for (int i = static_cast<int>(position.second) - 1; i >= 0; i--)
    {
        if (gameBoard[i][position.first].valueType == GameBoardTile::ValueType::EMPTY)
        {
            res.reserve(position.second - i - 1);
            for (int j = i + 1; j < position.second; j++)
                res.push_back(gameBoard[j][position.first].toScrabbleLetter());

            return res;
        }
    }

    // case when word starts at the top of the board
    res.reserve(std::max(0, static_cast<int>(position.second) - 1));
    for (int j = 0; j < position.second; j++)
        res.push_back(gameBoard[j][position.first].toScrabbleLetter());

    return res;
}

ScrabbleString findSufixForPos(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position)
{
    logger::debug("GameBoardHelpers::findSufixForPos(", gameBoard, static_cast<std::size_t>(position.first), ' ',
                 static_cast<std::size_t>(position.second), ")\n");

    ScrabbleString res;
    for (int i = static_cast<int>(position.second) + 1; i < GameBoard::size; i++)
    {
        if (gameBoard[i][position.first].valueType == GameBoardTile::ValueType::EMPTY)
        {
            res.reserve(i - position.second - 1);
            for (int j = position.second + 1; j < i; j++)
                res.push_back(gameBoard[j][position.first].toScrabbleLetter());

            return res;
        }
    }

    // case when word ends at the bottom of the board
    res.reserve(GameBoard::size - position.second);
    for (int j = position.second + 1; j < GameBoard::size; j++)
        res.push_back(gameBoard[j][position.first].toScrabbleLetter());

    return res;
}
