#ifndef LETTERSRENUMBERER_HPP
#define LETTERSRENUMBERER_HPP

#include "ILettersRenumberer.hpp"

#include <string>
#include <array>
#include <vector>
#include <unordered_map>

class LettersRenumberer: public ILettersRenumberer
{
public:
    LettersRenumberer(const std::vector<wchar_t>& letters);
    wchar_t getLetterFromNum(uint8_t num) override;
    uint8_t getNumFromLetter(wchar_t letter) override;
    bool isNumberValid(uint8_t num) override;
    bool isLetterValid(wchar_t letter) override;

private:
    std::array<wchar_t, 256> numToLetter_;
    std::unordered_map<wchar_t, uint8_t> letterToNum_;
    std::size_t counter_;
};

#endif // LETTERSRENUMBERER_HPP
