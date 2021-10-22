#include "ShowUserLettersCommand.hpp"

ShowUserLettersCommand::ShowUserLettersCommand(std::shared_ptr<IUserLettersDisplay> userLettersDisplay, std::shared_ptr<IScrabbleTextEdit> userLettersTextEdit)
    :userLettersDisplay_(userLettersDisplay), userLettersTextEdit_(userLettersTextEdit) { }

bool ShowUserLettersCommand::execute()
{
    IUserLettersDisplay::DataType letters;
    ScrabbleString userLetters = userLettersTextEdit_->getText();
    if (userLetters.empty())
    {
        userLettersDisplay_->hideUserLettersView();
        return false;
    }

    for (std::size_t i = 0; i < userLetters.size(); i++)
        letters[i] = userLetters[i];

    if (userLettersDisplay_->getViewdUserLetters() == letters)
        return false;

    userLettersDisplay_->showUserLettersView(letters);
    return true;
}
