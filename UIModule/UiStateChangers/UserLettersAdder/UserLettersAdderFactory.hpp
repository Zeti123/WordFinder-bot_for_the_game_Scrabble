#pragma once

#include "UserLettersAdder.hpp"

#include <QPushButton>

#include "IUserLettersDisplay.hpp"

class MainWindow;

class UserLettersAdderFactory
{
public:
    static std::shared_ptr<UserLettersAdder> create(MainWindow& mainWindow,
                                                    std::shared_ptr<IUserLettersDisplay> userLettersDisplay,
                                                    std::shared_ptr<IScrabbleTextEdit> userLetters,
                                                    QPushButton& applyButton,
                                                    std::shared_ptr<ICommandListManager> commandList);
};
