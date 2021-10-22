#include "GameBoard.hpp"
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

WordPlacement::WordPlacement(const ScrabbleString& word, std::pair<uint8_t, uint8_t> position, Orientation orientation)
    :word(word), position(position), orientation(orientation) { }

GameBoard GameBoard::reflectGameBoard(const GameBoard& gameBoard)
{
    logger::debug("GameBoard::reflectGameBoard(", gameBoard, ")\n");
    GameBoard res;
    for (size_t i = 0; i < GameBoard::size; i++)
        for (size_t j = 0; j < GameBoard::size; j++)
            res[i][j] = gameBoard[j][i];

    return res;
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

bool GameBoard::operator==(const GameBoard& right) const
{
    return board_ == right.board_;
}

bool GameBoard::operator!=(const GameBoard& right) const
{
    return board_ != right.board_;
}

WordPlacement GameBoard::findWordVerticallyCrossedBy(std::pair<uint8_t, uint8_t> position) const
{
    logger::debug("GameBoard::findWordVerticallyCrossedBy(", static_cast<std::pair<std::size_t, std::size_t>>(position), ")\n");
    ScrabbleString prefix = findPrefixForPos(position);
    ScrabbleString sufix = findSufixForPos(position);
    ScrabbleString str = prefix + board_[position.second][position.first].toScrabbleLetter() + sufix;
    auto resultPosition = std::make_pair(position.first, position.second - prefix.size());
    Orientation orientation = Orientation::VERTICAL;
    return WordPlacement(str, resultPosition, orientation);
}

WordPlacement GameBoard::findWordHorizontallyCrossedBy(std::pair<uint8_t, uint8_t> position) const
{
    logger::debug("GameBoard::findWordHorizontallyCrossedBy(", static_cast<std::pair<std::size_t, std::size_t>>(position), ")\n");
    GameBoard gameBoard = GameBoard::reflectGameBoard(*this);
    auto placement = gameBoard.findWordVerticallyCrossedBy(std::make_pair(position.second, position.first));
    placement.orientation = Orientation::HORIZONTAL;
    std::swap(placement.position.second, placement.position.first);
    return placement;
}

ScrabbleString GameBoard::findPrefixForPos(std::pair<uint8_t, uint8_t> position) const
{
    logger::debug("GameBoard::findPrefixForPos(", *this, static_cast<std::size_t>(position.first), ' ', 
                 static_cast<std::size_t>(position.second), ")\n");
    ScrabbleString res;
    for (int i = static_cast<int>(position.second) - 1; i >= 0; i--)
    {
        if (board_[i][position.first].valueType == GameBoardTile::ValueType::EMPTY)
        {
            res.reserve(position.second - i - 1);
            for (int j = i + 1; j < position.second; j++)
                res.push_back(board_[j][position.first].toScrabbleLetter());
            
            return res;
        }
    }

    // case when word starts at the top of the board
    res.reserve(std::max(0, static_cast<int>(position.second) - 1));
    for (int j = 0; j < position.second; j++)
        res.push_back(board_[j][position.first].toScrabbleLetter());
    
    return res;
}

ScrabbleString GameBoard::findSufixForPos(std::pair<uint8_t, uint8_t> position) const
{
    logger::debug("GameBoard::findSufixForPos(", *this, static_cast<std::size_t>(position.first), ' ', 
                 static_cast<std::size_t>(position.second), ")\n");
    ScrabbleString res;
    for (int i = static_cast<int>(position.second) + 1; i < GameBoard::size; i++)
    {
        if (board_[i][position.first].valueType == GameBoardTile::ValueType::EMPTY)
        {
            res.reserve(i - position.second - 1);
            for (int j = position.second + 1; j < i; j++)
                res.push_back(board_[j][position.first].toScrabbleLetter());
            
            return res;
        }
    }

    // case when word ends at the bottom of the board
    res.reserve(GameBoard::size - position.second);
    for (int j = position.second + 1; j < GameBoard::size; j++)
        res.push_back(board_[j][position.first].toScrabbleLetter());

    return res;
}

void GameBoard::putWord(const ScrabbleString& str, std::pair<uint8_t, uint8_t> place, Orientation orientation)
{
    logger::debug("GameBoard::putWord(", str, ' ', static_cast<std::pair<std::size_t, std::size_t>>(place), ' ', orientation,")\n");
    for (size_t i = 0; i < str.size(); i++)
    {
        auto x = (orientation == Orientation::HORIZONTAL) * i + place.first;
        auto y = (orientation == Orientation::VERTICAL) * i + place.second;
        auto valueType = (str[i].type == ScrabbleLetter::Type::NORMAL_TILE) ? GameBoardTile::ValueType::NORMAL_TILE
                                                                            : GameBoardTile::ValueType::EMPTY_TILE;

        if (x >= GameBoard::size || y >= GameBoard::size)
            return;

        board_[y][x] = GameBoardTile(str[i].letter, valueType);
    }
}

void GameBoard::putWord(const std::vector<GameBoardTile>& str, std::pair<uint8_t, uint8_t> place, Orientation orientation)
{
    logger::debug("GameBoard::putWord(", str, ' ', static_cast<std::pair<std::size_t, std::size_t>>(place), ' ', orientation,")\n");
    for (size_t i = 0; i < str.size(); i++)
    {
        auto x = (orientation == Orientation::HORIZONTAL) * i + place.first;
        auto y = (orientation == Orientation::VERTICAL) * i + place.second;
        if (x >= GameBoard::size || y >= GameBoard::size)
            return;

        board_[y][x] = GameBoardTile(str[i]);
    }
}

void GameBoard::putWord(const WordPlacement& wordPlacement)
{
    putWord(wordPlacement.word, wordPlacement.position, wordPlacement.orientation);
}

std::vector<GameBoardTile> GameBoard::getWordFromPlacement(const WordPlacement& placement)
{
    logger::debug("GameBoard::getWordFromPlacement(", placement.word, ' ', static_cast<std::pair<std::size_t, std::size_t>>(placement.position),
                 ' ', placement.orientation,")\n");

    std::vector<GameBoardTile> word;
    for (size_t i = 0; i < placement.word.size(); i++)
    {
        auto x = (placement.orientation == Orientation::HORIZONTAL) * i + placement.position.first;
        auto y = (placement.orientation == Orientation::VERTICAL) * i + placement.position.second;
        if (x >= GameBoard::size || y >= GameBoard::size)
            return {};

        word.push_back(board_[y][x]);
    }
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

std::ostream& operator<<(std::ostream& out, const WordPlacement& wordPlacement)
{
    out << '(' << wordPlacement.word << ", " << static_cast<std::pair<std::size_t, std::size_t>>(wordPlacement.position) << ", " 
        << wordPlacement.orientation << ')';
    return out;
}

std::ostream& operator<<(std::ostream& out, Orientation orientation)
{
    out << (orientation == Orientation::HORIZONTAL ? 'H' : 'V');
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
