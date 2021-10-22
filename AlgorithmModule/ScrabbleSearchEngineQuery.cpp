#include "ScrabbleSearchEngineQuery.hpp"

ScrabbleSearchEngineQuery::ScrabbleSearchEngineQuery(const GameBoard& gameBoard, const ScrabbleString& userLetters)
	:gameBoard(gameBoard), userLetters(userLetters) { }
