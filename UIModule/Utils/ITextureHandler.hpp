#ifndef ITEXTUREHANDLER_H
#define ITEXTUREHANDLER_H

#include <cstdint>
#include <QPixmap>

class ITextureHandler
{
public:
    enum class FieldTextureType
    {
        TRANSPARMENT,
        EMPTY_TILE,
        NORMAL,
        LETTERX2,
        LETTERX3,
        WORDX2,
        WORDX3
    };

public:
    virtual QPixmap getLetterTexture(uint8_t textureNum) = 0;
    virtual QPixmap& getTileTexture(FieldTextureType textureType) = 0;
    virtual QPixmap getEmptyTileForLetter(u_int8_t textureNum) = 0;
};

#endif // ITEXTUREHANDLER_H
