#ifndef TEXTUREHANDELER_HPP
#define TEXTUREHANDELER_HPP

#include "ITextureHandeler.hpp"
#include "ILettersRenumberer.hpp"
#include "LettersInfo.hpp"

#include <memory>

class TextureHandeler: public ITextureHandeler
{
public:
    TextureHandeler(const std::wstring& texturesPath, std::shared_ptr<ILettersRenumberer> renumberer, std::shared_ptr<LettersInfo> lettersInfo);
    QPixmap getLetterTexture(uint8_t textureNum) override;
    QPixmap& getTileTexture(FieldTextureType textureType) override;
    QPixmap getEmptyTileForLetter(u_int8_t textureNum) override;

private:
    void drawCharOnTexture(QPixmap& pixmap, QChar ch, uint8_t letterScore, QColor color);
    std::shared_ptr<ILettersRenumberer> renumberer_;
    std::shared_ptr<LettersInfo> lettersInfo_;
    std::array<QPixmap, 7> tileBuffer_;
};

#endif // TEXTUREHANDELER_HPP
