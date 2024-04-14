#include "GameBoardTilesEraserFactory.hpp"

#include "MainWindow.hpp"

#include "EraseFromGameBoardCommand.hpp"

std::shared_ptr<GameBoardTilesEraser> GameBoardTilesEraserFactory::create(MainWindow& mainWindow,
                                                                          std::shared_ptr<IGameBoardDisplay> gameBoard,
                                                                          std::shared_ptr<ISwitch> onOffswitch,
                                                                          std::shared_ptr<ICommandListManager> commandsList)
{
    auto gameBoardTilesEraser = std::make_shared<GameBoardTilesEraser>(onOffswitch, std::make_shared<EraseFromGameBoardCommand>(gameBoard), commandsList);;
    mainWindow.connect(gameBoard.get(), &IGameBoardDisplay::selectionChanged, gameBoardTilesEraser.get(), &GameBoardTilesEraser::receiveGameBoardSelectionChange);
    return gameBoardTilesEraser;
}
