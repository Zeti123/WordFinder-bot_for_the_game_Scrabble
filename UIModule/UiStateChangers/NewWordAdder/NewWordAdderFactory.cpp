#include "NewWordAdderFactory.hpp"

#include <QPushButton>

#include "PutWordOnGameBoardCommand.hpp"
#include "PutAndSaveWordOnGameBoardCommand.hpp"

#include "MainWindow.hpp"

std::shared_ptr<NewWordAdder> NewWordAdderFactory::create(MainWindow& mainWindow, std::shared_ptr<IGameBoardDisplay> gameBoard, std::shared_ptr<ISwitch> orientationSwitch, std::shared_ptr<IScrabbleTextEdit> textEdit, QPushButton& applyButton, std::shared_ptr<ICommandListManager> commandsList)
{
    auto newWordAdder = std::make_shared<NewWordAdder>(orientationSwitch, textEdit,
                                                       std::make_shared<PutWordOnGameBoardCommand>(gameBoard, textEdit, orientationSwitch),
                                                       std::make_shared<PutAndSaveWordOnGameBoardCommand>(gameBoard, textEdit, orientationSwitch),
                                                       commandsList);
    mainWindow.connect(&applyButton, &QPushButton::clicked, newWordAdder.get(), &NewWordAdder::receiveApplyClick);
    mainWindow.connect(gameBoard.get(), &IGameBoardDisplay::selectionChanged, newWordAdder.get(), &NewWordAdder::receiveGameBoardSelectionChange);

    return newWordAdder;
}
