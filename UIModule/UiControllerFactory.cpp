#include "UiControllerFactory.hpp"

#include "MainWindow.hpp"

#include "UiController.hpp"
#include "ResultsListsFactory.hpp"
#include "GameBoardDisplayFactory.hpp"
#include "UserLettersFactory.hpp"
#include "UiStateChangersFactory.hpp"

std::unique_ptr<IUiController> UiControllerFactory::create(MainWindow& mainWindow, Ui::MainWindow& mainWindowUi,
                                                           std::shared_ptr<ILettersRenumberer> lettersRenumberer,
                                                           std::shared_ptr<ITextureHandler> textureHandler)
{
    auto wordsList = ResultsListsFactory::create(*mainWindowUi.list_of_words, lettersRenumberer);

    auto board = GameBoardDisplayFactory::create(*mainWindowUi.game_board, textureHandler);
    auto userLettersDisplay = UserLettersFactory::create(*mainWindowUi.user_letters, textureHandler);

    auto stateChangers = UiStateChangersFactory::create(mainWindow, mainWindowUi, lettersRenumberer, board, userLettersDisplay, wordsList);
    return std::make_unique<UiController>(board, userLettersDisplay, wordsList, stateChangers);
}
