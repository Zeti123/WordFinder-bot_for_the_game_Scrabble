#pragma once

#include "NewWordAdder.hpp"

#include <QPushButton>>

#include "IGameBoardDisplay.hpp"

class MainWindow;

class NewWordAdderFactory
{
public:
    static std::shared_ptr<NewWordAdder> create(MainWindow& mainWindow,
                                                std::shared_ptr<IGameBoardDisplay> gameBoard,
                                                std::shared_ptr<ISwitch> orientationSwitch,
                                                std::shared_ptr<IScrabbleTextEdit> textEdit,
                                                QPushButton& applyButton,
                                                std::shared_ptr<ICommandListManager> commandsList);
};
