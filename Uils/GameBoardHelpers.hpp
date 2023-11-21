#pragma once

#include "GameBoard.hpp"

GameBoard reflectGameBoard(const GameBoard& gameBoard);
WordPlacement findWordVerticallyCrossedBy(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position);
WordPlacement findWordHorizontallyCrossedBy(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position);
ScrabbleString findPrefixForPos(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position);
ScrabbleString findSufixForPos(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position);
