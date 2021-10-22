#include "TextureHandeler.hpp"

#include <fstream>

#include <QPainter>
#include <QPaintEngine>

TextureHandeler::TextureHandeler(const std::wstring& texturesPath, std::shared_ptr<ILettersRenumberer> renumberer, std::shared_ptr<LettersInfo> lettersInfo)
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

QPixmap TextureHandeler::getLetterTexture(uint8_t textureNum)
{
    if (!renumberer_->isNumberValid(textureNum))
        std::runtime_error("no letter with number: " + std::to_string(textureNum));

    auto letter = renumberer_->getLetterFromNum(textureNum);
    auto emptyTextureCopy = getTileTexture(FieldTextureType::EMPTY_TILE);
    auto letterScore = lettersInfo_->getLetterScore(textureNum);

    drawCharOnTexture(emptyTextureCopy, QChar(letter), letterScore, QColor(0, 0, 0));

    return emptyTextureCopy;
}

QPixmap& TextureHandeler::getTileTexture(ITextureHandeler::FieldTextureType textureType)
{
    return tileBuffer_[static_cast<int>(textureType)];
}

QPixmap TextureHandeler::getEmptyTileForLetter(u_int8_t textureNum)
{
    if (!renumberer_->isNumberValid(textureNum))
        std::runtime_error("no letter with number: " + std::to_string(textureNum));

    auto letter = renumberer_->getLetterFromNum(textureNum);
    auto emptyTextureCopy = getTileTexture(FieldTextureType::EMPTY_TILE);

    drawCharOnTexture(emptyTextureCopy, QChar(letter), 0, QColor(50, 50, 50, 50));

    return emptyTextureCopy;
}

void TextureHandeler::drawCharOnTexture(QPixmap& pixmap, QChar ch, uint8_t letterScore, QColor color)
{
    QPainter painter(&pixmap);
    painter.setPen(color);
    auto font = QFont("Arial");
    font.setBold(true);
    font.setPointSize(31);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, 58, 58), Qt::AlignCenter, ch.toUpper());
    QFontMetrics metrics(font);

    font.setPointSize(8);
    painter.setFont(font);

    painter.drawText(QRect(QPoint(40, 40), QPoint(55, 55)), Qt::AlignCenter, QString::fromStdString(std::to_string(letterScore)));
}
