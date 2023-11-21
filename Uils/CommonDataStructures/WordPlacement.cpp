#include "WordPlacement.hpp"

#include <ostream>

#include "log.hpp"

WordPlacement::WordPlacement(const ScrabbleString& word, std::pair<uint8_t, uint8_t> position, Orientation orientation)
    :word(word), position(position), orientation(orientation) { }

std::ostream& operator << (std::ostream& ostream, Orientation orientation)
{
    ostream << (orientation == Orientation::HORIZONTAL ? 'H' : 'V');
    return ostream;
}

std::ostream& operator << (std::ostream& ostream, const WordPlacement& wordPlacement)
{
    ostream << '(' << wordPlacement.word << ", " << static_cast<std::pair<std::size_t, std::size_t>>(wordPlacement.position) << ", "
        << wordPlacement.orientation << ')';
    return ostream;
}
