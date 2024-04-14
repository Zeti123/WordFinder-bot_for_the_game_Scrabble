#pragma once

#include "GameBoardTilesEraser.hpp"
#include "IGameBoardDisplay.hpp"

class MainWindow;

class GameBoardTilesEraserFactory
{
public:
    static std::shared_ptr<GameBoardTilesEraser> create(MainWindow& mainWindow, std::shared_ptr<IGameBoardDisplay> gameBoard, std::shared_ptr<ISwitch> onOffswitch, std::shared_ptr<ICommandListManager> commandsList);
};
