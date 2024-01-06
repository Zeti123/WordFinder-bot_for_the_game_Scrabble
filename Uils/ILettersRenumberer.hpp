#ifndef ILETTERSRENUMBER_HPP
#define ILETTERSRENUMBER_HPP

#include <cwchar>
#include <cstdint>

class ILettersRenumberer
{
public:
    virtual ~ILettersRenumberer() = default;
    virtual wchar_t getLetterFromNum(uint8_t num) = 0;
    virtual uint8_t getNumFromLetter(char32_t letter) = 0;
    virtual bool isNumberValid(uint8_t num) = 0;
    virtual bool isLetterValid(char32_t letter) = 0;
};

#endif // ILETTERSRENUMBER_HPP
