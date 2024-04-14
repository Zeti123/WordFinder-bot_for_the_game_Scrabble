#include "UiStateChangersFactory.hpp"

#include "MainWindow.hpp"

#include "GameBoardTilesEraserFactory.hpp"
#include "NewWordAdderFactory.hpp"
#include "TimeTraveler.hpp"
#include "UserLettersAdderFactory.hpp"
#include "WordsFromListAdderFactory.hpp"
#include "RadioButtonSwitch.hpp"
#include "LineTextScrabbleTextEdit.hpp"
#include "CommandListManager.hpp"

std::vector<std::shared_ptr<IUiStateChanger>> UiStateChangersFactory::create(MainWindow& mainWindow,
                                                                             Ui::MainWindow& mainWindowUi,
                                                                             std::shared_ptr<ILettersRenumberer> lettersRenumberer,
                                                                             std::shared_ptr<IGameBoardDisplay> gameBoard,
                                                                             std::shared_ptr<IUserLettersDisplay> userLettersDisplay,
                                                                             std::shared_ptr<IList> resultsList)
{
    auto commandsList = std::make_shared<CommandListManager>();

    auto eraseSwitch = std::make_shared<RadioButtonSwitch>(*mainWindowUi.erase_on, *mainWindowUi.erase_of, false);
    auto gameBoardTilesEraser = GameBoardTilesEraserFactory::create(mainWindow, gameBoard, eraseSwitch, commandsList);

    auto newWordLineEdit = std::make_shared<LineTextScrabbleTextEdit>(*mainWindowUi.word_adder, lettersRenumberer);
    auto orientationSwitch = std::make_shared<RadioButtonSwitch>(*mainWindowUi.orientation_vertical, *mainWindowUi.orientation_horizontal, false);
    auto newWordAdder = NewWordAdderFactory::create(mainWindow, gameBoard, orientationSwitch, newWordLineEdit, *mainWindowUi.new_word_apply, commandsList);

    auto undoShortcut = std::make_unique<QShortcut>(QKeySequence(Qt::CTRL | Qt::Key_Z), &mainWindow);
    auto redoShortcut = std::make_unique<QShortcut>(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Z), &mainWindow);
    auto timeTraveler = std::make_shared<TimeTraveler>(*mainWindowUi.undo, *mainWindowUi.redo, commandsList, std::move(undoShortcut), std::move(redoShortcut));

    auto scrabbleTextEdit = std::make_shared<LineTextScrabbleTextEdit>(*mainWindowUi.user_letters_line_edit, lettersRenumberer, true);
    auto userLettersAdder = UserLettersAdderFactory::create(mainWindow, userLettersDisplay, scrabbleTextEdit, *mainWindowUi.user_letters_apply, commandsList);

    auto searchBar = std::make_shared<LineTextScrabbleTextEdit>(*mainWindowUi.search_bar, lettersRenumberer);
    auto wordsListAdder = WordsFromListAdderFactory::create(mainWindow, gameBoard, searchBar, resultsList, *mainWindowUi.search_apply, commandsList);

    return std::vector<std::shared_ptr<IUiStateChanger>>{gameBoardTilesEraser, newWordAdder, timeTraveler, userLettersAdder, wordsListAdder};
}
