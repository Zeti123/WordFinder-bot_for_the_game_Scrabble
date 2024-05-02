#pragma once

#include "IUiController.hpp"

#include <memory>

#include "ui_MainWindow.h"

#include "ILettersRenumberer.hpp"
#include "ITextureHandler.hpp"

class MainWindow;

class UiControllerFactory
{
public:
    std::unique_ptr<IUiController> create(MainWindow& mainWindow, Ui::MainWindow& mainWindowUi,
        std::shared_ptr<ILettersRenumberer> lettersRenumberer, std::shared_ptr<ITextureHandler> textureHandler);
};
