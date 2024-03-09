#pragma once

#include <QTableView>
#include <IGameBoardDisplay.hpp>

#include "ITextureHandler.hpp"

class GameBoardDisplayFactory
{
public:
    std::shared_ptr<IGameBoardDisplay> create(QTableView& tableView,
                                              const std::shared_ptr<ITextureHandler>& textureHandler);
};
