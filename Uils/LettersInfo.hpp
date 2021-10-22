#pragma once

#include <array>
#include <vector>
#include <cstdint>

class LettersInfo
{
public:
    LettersInfo(const std::vector<std::pair<char, std::size_t>>& letters);
    void addLetterInfo(char letter, std::size_t score);
    std::size_t getLetterScore(char letter) const;
    std::vector<char> getAllLetters() const;

private:
    std::array<std::size_t, 256> letterScore_;
};
