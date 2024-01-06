#ifndef POLISHDEBUGRENUMBERER_HPP
#define POLISHDEBUGRENUMBERER_HPP

#include <ILettersRenumberer.hpp>
#include <array>

class PolishDebugRenumberer: public ILettersRenumberer
{
public:
    PolishDebugRenumberer();
    wchar_t getLetterFromNum(uint8_t num) override;
    uint8_t getNumFromLetter(char32_t letter) override;
    bool isNumberValid(uint8_t num) override;
    bool isLetterValid(char32_t letter) override;

private:
    std::array<std::pair<char32_t, uint8_t>, 9> polishLetters_;
};

#endif // POLISHDEBUGRENUMBERER_HPP
