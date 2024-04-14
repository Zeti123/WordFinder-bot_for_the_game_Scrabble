#include "WordsFromListAdderFactory.hpp"

#include "MainWindow.hpp"

#include "SelectWordFromListCommand.hpp"
#include "ShowWordFromListCommand.hpp"

std::shared_ptr<SearchListController> WordsFromListAdderFactory::create(MainWindow& mainWindow,
                                                                        std::shared_ptr<IGameBoardDisplay> display,
                                                                        std::shared_ptr<IScrabbleTextEdit> searchBar,
                                                                        std::shared_ptr<IList> listOfWords,
                                                                        QPushButton& applyButton,
                                                                        std::shared_ptr<ICommandListManager> commandsList)
{
    auto searchListController = std::make_shared<SearchListController>(searchBar, listOfWords,
                                                                       std::make_shared<ShowWordFromListCommand>(display, listOfWords),
                                                                       std::make_shared<SelectWordFromListCommand>(display, listOfWords),
                                                                       commandsList);

    mainWindow.connect(&applyButton, &QPushButton::clicked, searchListController.get(), &SearchListController::receiveApply);
    return searchListController;
}
