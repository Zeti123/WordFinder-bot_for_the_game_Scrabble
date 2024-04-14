#pragma once

#include "SearchListController.hpp"

#include <QPushButton>

#include "IGameBoardDisplay.hpp"

class MainWindow;

class WordsFromListAdderFactory
{
public:
    static std::shared_ptr<SearchListController> create(MainWindow& mainWindow,
                                                        std::shared_ptr<IGameBoardDisplay> display,
                                                        std::shared_ptr<IScrabbleTextEdit> searchBar,
                                                        std::shared_ptr<IList> listOfWords,
                                                        QPushButton& applyButton,
                                                        std::shared_ptr<ICommandListManager> commandsList);
};
