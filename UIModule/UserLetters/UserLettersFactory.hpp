#pragma once

#include "IUserLettersDisplay.hpp"

#include <memory>

#include <QTableView>

#include "ITextureHandler.hpp"

class UserLettersFactory
{
public:
    static std::shared_ptr<IUserLettersDisplay> create(QTableView& listView, std::shared_ptr<ITextureHandler> textureHandler);
};
