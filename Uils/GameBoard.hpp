#pragma once

#include "ScrabbleString.hpp"

#include <array>
#include <cstdint>
#include <string>
#include <ostream>
#include <vector>

enum class Orientation
{
    VERTICAL, HORIZONTAL
};

enum class FieldBonus: uint8_t
{
    NONE = 0,
    LETTERX2 = 1,
    LETTERX3 = 2,
    WORDX2 = 3,
    WORDX3 = 4
};

struct GameBoardTile
{
    enum class ValueType : uint8_t 
    {
        EMPTY, EMPTY_TILE, NORMAL_TILE
    };
    GameBoardTile();
    GameBoardTile(char value, ValueType type);
    GameBoardTile& operator=(const GameBoardTile&) = default;
    ScrabbleLetter toScrabbleLetter() const;

    char value;
    ValueType valueType;
};

struct WordPlacement
{
    WordPlacement(const ScrabbleString& word, std::pair<uint8_t, uint8_t> position, Orientation orientation);

    ScrabbleString word;
    std::pair<uint8_t, uint8_t> position;
    Orientation orientation;
};

class GameBoard
{
public:
    constexpr static uint8_t size = 15;
    static GameBoard reflectGameBoard(const GameBoard& gameBoard);
    static FieldBonus getFieldBonus(uint8_t x, uint8_t y);

    std::array<GameBoardTile, 15>& operator[](std::size_t index);
    const std::array<GameBoardTile, 15>& operator[](std::size_t index) const;
    bool operator==(const GameBoard& right) const;
    bool operator!=(const GameBoard& right) const;
    WordPlacement findWordVerticallyCrossedBy(std::pair<uint8_t, uint8_t> position) const;
    WordPlacement findWordHorizontallyCrossedBy(std::pair<uint8_t, uint8_t> position) const;
    ScrabbleString findPrefixForPos(std::pair<uint8_t, uint8_t> position) const;
    ScrabbleString findSufixForPos(std::pair<uint8_t, uint8_t> position) const;
    void putWord(const ScrabbleString& str, std::pair<uint8_t, uint8_t> place, Orientation orientation);
    void putWord(const std::vector<GameBoardTile>& str, std::pair<uint8_t, uint8_t> place, Orientation orientation);
    void putWord(const WordPlacement& wordPlacement);
    std::vector<GameBoardTile> getWordFromPlacement(const WordPlacement& placement);

private:
    std::array<std::array<GameBoardTile, size>, size> board_;
    static constexpr std::array<std::array<uint8_t, size>, size> bonuses = {{  
            {{4, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 4}},
            {{0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0}},
            {{0, 0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0}},
            {{1, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 1}},
            {{0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0}},
            {{0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0}},
            {{0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0}},
            {{4, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 4}},
            {{0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0}},
            {{0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0}},
            {{0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0}},
            {{1, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 1}},
            {{0, 0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0}},
            {{0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0}},
            {{4, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 4}}
    }};

public:
    using iterator = typename decltype(board_)::iterator;
    using const_iterator = typename decltype(board_)::const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};

using LineType = std::array<GameBoardTile, GameBoard::size>;

bool operator==(const GameBoardTile& left, const GameBoardTile& right);
std::string operator+(const std::string& str, const GameBoardTile& letter);
std::string operator+(const GameBoardTile& letter, const std::string& str);
std::string operator+(const std::string& str, const LineType& line);
std::string operator+(const LineType& line, const std::string& str);
std::ostream& operator<<(std::ostream& out, GameBoardTile letter);
std::ostream& operator<<(std::ostream& out, const LineType& line);
std::ostream& operator<<(std::ostream& out, const GameBoard& line);
std::ostream& operator<<(std::ostream& out, const WordPlacement& wordPlacement);
std::ostream& operator<<(std::ostream& out, Orientation orientation);
