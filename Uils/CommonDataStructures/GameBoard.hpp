#pragma once

#include <array>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

#include "ScrabbleString.hpp"
#include "WordPlacement.hpp"

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
    ScrabbleLetter toScrabbleLetter() const;

    char value;
    ValueType valueType;
};

class GameBoard
{
public:
    constexpr static uint8_t size = 15;
    static FieldBonus getFieldBonus(uint8_t x, uint8_t y);

    std::array<GameBoardTile, 15>& operator[](std::size_t index);
    const std::array<GameBoardTile, 15>& operator[](std::size_t index) const;
    bool operator == (const GameBoard& other) const;
    bool operator != (const GameBoard& other) const;

    bool isEmpty() const;
    std::vector<GameBoardTile> getWordFromPlacement(const WordPlacement& placement) const;

    void placeWord(const std::vector<GameBoardTile>& word, std::pair<uint8_t, uint8_t> position, Orientation orientation);
    void placeWord(const WordPlacement& wordPlacement);

private:
    static constexpr std::array<std::array<uint8_t, size>, size> bonuses = {{  
            {{4, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 4}},
            {{0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0}},
            {{0, 0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0}},
            {{1, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 1}},
            {{0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0}},
            {{0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0}},
            {{0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0}},
            {{4, 0, 0, 1, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 4}},
            {{0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0}},
            {{0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 0}},
            {{0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0}},
            {{1, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 3, 0, 0, 1}},
            {{0, 0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0}},
            {{0, 3, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 3, 0}},
            {{4, 0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 4}}
    }};
    std::array<std::array<GameBoardTile, size>, size> board_;

public:
    using iterator = typename decltype(board_)::iterator;
    using const_iterator = typename decltype(board_)::const_iterator;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};

using LineType = std::array<GameBoardTile, GameBoard::size>;

bool operator == (const GameBoardTile& l, const GameBoardTile& r);
std::string operator + (const std::string& str, const GameBoardTile& letter);
std::string operator + (const GameBoardTile& letter, const std::string& str);
std::string operator + (const std::string& str, const LineType& line);
std::string operator + (const LineType& line, const std::string& str);
std::ostream& operator << (std::ostream& ostream, GameBoardTile letter);
std::ostream& operator << (std::ostream& ostream, const LineType& line);
std::ostream& operator << (std::ostream& ostream, const GameBoard& line);
