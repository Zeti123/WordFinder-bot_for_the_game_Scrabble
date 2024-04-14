#include "UserLettersAdderFactory.hpp"

#include "MainWindow.hpp"

#include "ShowUserLettersCommand.hpp"
#include "SetUserLettersCommand.hpp"

std::shared_ptr<UserLettersAdder> UserLettersAdderFactory::create(MainWindow& mainWindow, std::shared_ptr<IUserLettersDisplay> userLettersDisplay, std::shared_ptr<IScrabbleTextEdit> userLetters, QPushButton& applyButton, std::shared_ptr<ICommandListManager> commandList)
{
    auto userLettersAdder = std::make_shared<UserLettersAdder>(userLetters,
                                                               std::make_shared<ShowUserLettersCommand>(userLettersDisplay, userLetters),
                                                               std::make_shared<SetUserLettersCommand>(userLettersDisplay, userLetters),
                                                               commandList);
    mainWindow.connect(&applyButton, &QPushButton::clicked, userLettersAdder.get(), &UserLettersAdder::receiveApplyClick);

    return userLettersAdder;
}
