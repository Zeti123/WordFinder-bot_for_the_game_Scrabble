#include "TextureHandler.hpp"

#include <stdexcept>

#include <QPainter>
#include <QPaintEngine>

TextureHandler::TextureHandler(const std::wstring& texturesPath, std::shared_ptr<ILettersRenumberer> renumberer, std::shared_ptr<LettersInfo> lettersInfo)
    :renumberer_(renumberer), lettersInfo_(lettersInfo)
{
    const std::vector<std::wstring> fileFiledNames = {L"transparment_tile", L"empty_tile", L"normal_tile", L"letterx2_tile", L"letterx3_tile", L"wordx2_tile", L"wordx3_tile"};
    for (std::size_t i = 0; i < fileFiledNames.size(); i++)
    {
        auto fullFilePath = texturesPath + fileFiledNames[i] + L".png";
        bool success = tileBuffer_[i].load(QString::fromStdWString(fullFilePath));

        if (!success)
            std::runtime_error("cannot load field texture");
    }
}

QPixmap TextureHandler::getLetterTexture(uint8_t textureNum, size_t size)
{
    if (!renumberer_->isNumberValid(textureNum))
        std::runtime_error("no letter with number: " + std::to_string(textureNum));

    auto letter = renumberer_->getLetterFromNum(textureNum);
    auto emptyTextureCopy = getTileTexture(FieldTextureType::EMPTY_TILE).scaled(QSize(size, size));
    auto letterScore = lettersInfo_->getLetterScore(textureNum);


    drawCharOnTexture(emptyTextureCopy, QChar(letter), letterScore, QColor(0, 0, 0), size);

    return emptyTextureCopy;
}

QPixmap& TextureHandler::getTileTexture(ITextureHandler::FieldTextureType textureType)
{
    return tileBuffer_[static_cast<int>(textureType)];
}

QPixmap TextureHandler::getEmptyTileForLetter(uint8_t textureNum, size_t size)
{
    if (!renumberer_->isNumberValid(textureNum))
        std::runtime_error("no letter with number: " + std::to_string(textureNum));

    auto letter = renumberer_->getLetterFromNum(textureNum);
    auto emptyTextureCopy = getTileTexture(FieldTextureType::EMPTY_TILE).scaled(QSize(size, size));

    drawCharOnTexture(emptyTextureCopy, QChar(letter), 0, QColor(50, 50, 50, 50), size);

    return emptyTextureCopy;
}

void TextureHandler::drawCharOnTexture(QPixmap& pixmap, QChar ch, uint8_t letterScore, QColor color, size_t size)
{
    constexpr float letterFontScale = 0.55;
    constexpr float scoreFontScale = 0.20;
    constexpr float scoreFontOffsetLeft = 0.65;
    constexpr float scoreFontOffsetTop = 0.6;

    QPainter painter(&pixmap);
    painter.setPen(color);
    auto font = QFont("Arial");
    font.setBold(true);
    font.setPointSize(size * letterFontScale);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, size, size), Qt::AlignCenter, ch.toUpper());

    font.setPointSize(size * scoreFontScale);
    font.setBold(false);
    painter.setFont(font);

    painter.drawText(QRect(QPoint(scoreFontOffsetLeft * size, scoreFontOffsetTop * size),
                           QPoint(size, size)),
                     Qt::AlignCenter, QString::fromStdString(std::to_string(letterScore)));
}
