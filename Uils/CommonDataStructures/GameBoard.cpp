#include "GameBoard.hpp"

#include <algorithm>

#include "log.hpp"

GameBoardTile::GameBoardTile()
    :value(0), valueType(ValueType::EMPTY) {}

GameBoardTile::GameBoardTile(char value, ValueType type)
    :value(value), valueType(type) {}

ScrabbleLetter GameBoardTile::toScrabbleLetter() const
{
    logger::debug("GameBoardLetter::toScrabbleLetter()\n");

    if (valueType == GameBoardTile::ValueType::EMPTY)
        throw std::runtime_error("cannot convert empty field to ScrabbleLetter");
    
    return (valueType == GameBoardTile::ValueType::NORMAL_TILE) ? 
        ScrabbleLetter(value, ScrabbleLetter::Type::NORMAL_TILE) : ScrabbleLetter(value, ScrabbleLetter::Type::EMPTY_TILE); 
}

FieldBonus GameBoard::getFieldBonus(uint8_t x, uint8_t y)
{
    logger::debug("GameBoard::getFieldBonus(", static_cast<std::size_t>(x), ' ', static_cast<std::size_t>(y), ")\n");
    return static_cast<FieldBonus>(bonuses[y][x]);
}

std::array<GameBoardTile, 15>& GameBoard::operator[](std::size_t index)
{
    return board_[index];
}

const std::array<GameBoardTile, 15>& GameBoard::operator[](std::size_t index) const
{
    return board_[index];
}

bool GameBoard::operator==(const GameBoard& other) const
{
    return board_ == other.board_;
}

bool GameBoard::operator!=(const GameBoard& other) const
{
    return board_ != other.board_;
}

bool GameBoard::isEmpty() const
{
    for (const auto& line: board_)
        for (const auto& field: line)
            if (field.valueType != GameBoardTile::ValueType::EMPTY)
                return false;

    return true;
}

void GameBoard::placeWord(const std::vector<GameBoardTile>& word, std::pair<uint8_t, uint8_t> position, Orientation orientation)
{
    logger::debug("GameBoard::placeWord(", word, ' ', static_cast<std::pair<std::size_t, std::size_t>>(position), ' ', orientation,")\n");

    for (size_t i = 0; i < word.size(); i++)
    {
        auto x = (orientation == Orientation::HORIZONTAL) * i + position.first;
        auto y = (orientation == Orientation::VERTICAL) * i + position.second;

        if (x >= GameBoard::size || y >= GameBoard::size)
            return;

        board_[y][x] = word[i];
    }
}

void GameBoard::placeWord(const WordPlacement& wordPlacement)
{
    const auto& [word, position, orientation] = wordPlacement;
    std::vector<GameBoardTile> gameBoardWord;
    gameBoardWord.reserve(word.size());
    std::transform(word.begin(), word.end(), std::back_inserter(gameBoardWord), [](ScrabbleLetter letter) {
        return GameBoardTile(letter.letter, letter.type == ScrabbleLetter::Type::NORMAL_TILE ? GameBoardTile::ValueType::NORMAL_TILE :
                                                                                               GameBoardTile::ValueType::EMPTY_TILE);
    });
    placeWord(gameBoardWord, position, orientation);
}

std::vector<GameBoardTile> GameBoard::getWordFromPlacement(const WordPlacement& placement) const
{
    logger::debug("GameBoard::getWordFromPlacement(", placement.word, ' ', static_cast<std::pair<std::size_t, std::size_t>>(placement.position),
                 ' ', placement.orientation,")\n");

    std::vector<GameBoardTile> word;
    word.reserve(15);
    for (size_t i = 0; i < placement.word.size(); i++)
    {
        auto x = (placement.orientation == Orientation::HORIZONTAL) * i + placement.position.first;
        auto y = (placement.orientation == Orientation::VERTICAL) * i + placement.position.second;
        if (x >= GameBoard::size || y >= GameBoard::size)
            return {};

        word.push_back(board_[y][x]);
    }
    word.shrink_to_fit();
    return word;
}

bool operator==(const GameBoardTile& left, const GameBoardTile& right)
{
    return (left.valueType == right.valueType && (left.valueType == GameBoardTile::ValueType::EMPTY || left.value == right.value));
}

std::string operator+(const std::string& str, const GameBoardTile& letter)
{
    std::string lineStr = "";
    if (letter.valueType == GameBoardTile::ValueType::EMPTY)
        lineStr += '.';
    else if (letter.valueType == GameBoardTile::ValueType::EMPTY_TILE)
        lineStr += std::string("(") + letter.value + ")";
    else 
        lineStr += letter.value;
    
    return str + lineStr;
}

std::string operator+(const GameBoardTile& letter, const std::string& str)
{
    return str + letter;
}

std::string operator+(const std::string& str, const LineType& line)
{
    std::string tmp;
    for (const auto& letter: line)
        tmp = tmp + letter;
    
    return str + tmp;
}

std::string operator+(const LineType& line, const std::string& str)
{
    return str + line;
}

std::ostream& operator<<(std::ostream& out, GameBoardTile letter)
{
    out << std::string("") + letter;
    return out;
}

std::ostream& operator<<(std::ostream& out, const LineType& line)
{
    out << std::string("") + line;
    return out;
}

std::ostream& operator<<(std::ostream& out, const GameBoard& gameBoard)
{
    for (size_t i = 0; i < GameBoard::size; i++)
        out<<gameBoard[i]<<std::endl;
    return out;
}

GameBoard::iterator GameBoard::begin()
{
    return board_.begin();
}
GameBoard::iterator GameBoard::end()
{
    return board_.end();
}

GameBoard::const_iterator GameBoard::begin() const
{
    return board_.begin();
}

GameBoard::const_iterator GameBoard::end() const
{
    return board_.end();
}
