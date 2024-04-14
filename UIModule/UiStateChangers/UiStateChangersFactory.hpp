#pragma once

#include "IUiStateChanger.hpp"

#include <memory>

#include "ui_MainWindow.h"

#include "IGameBoardDisplay.hpp"
#include "ILettersRenumberer.hpp"
#include "IUserLettersDisplay.hpp"
#include "IList.hpp"

class MainWindow;

class UiStateChangersFactory
{
public:
    static std::vector<std::shared_ptr<IUiStateChanger>> create(MainWindow& mainWindow,
                                                                Ui::MainWindow& mainWindowUi,
                                                                std::shared_ptr<ILettersRenumberer> lettersRenumberer,
                                                                std::shared_ptr<IGameBoardDisplay> gameBoard,
                                                                std::shared_ptr<IUserLettersDisplay> userLettersDisplay,
                                                                std::shared_ptr<IList> resultsList);
};
