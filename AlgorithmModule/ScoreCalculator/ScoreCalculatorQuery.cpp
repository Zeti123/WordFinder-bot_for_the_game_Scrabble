#include "ScoreCalculatorQuery.hpp"

ScoreCalculatorQuery::ScoreCalculatorQuery(const GameBoard& gameBoard, const std::vector<WordPlacement>& words)
    :gameBoard(gameBoard), words(words) {}