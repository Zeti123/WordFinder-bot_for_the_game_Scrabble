#include "UserLettersAdder.hpp"

UserLettersAdder::UserLettersAdder(std::shared_ptr<IScrabbleTextEdit> userLetters, std::shared_ptr<ICommand> showUserLettersView,
                                   std::shared_ptr<IReversableCommand> setUserLetters, std::shared_ptr<ICommandListManager> commandList)
    :userLetters_(userLetters), showUserLettersView_(showUserLettersView), setUserLetters_(setUserLetters), commandList_(commandList)
{
    connect(userLetters.get(), &IScrabbleTextEdit::textChanged, this, &UserLettersAdder::reveiveTextChanged);
}

void UserLettersAdder::lostFocus()
{
    QSignalBlocker(this);
    userLetters_->setText(ScrabbleString());
}

void UserLettersAdder::otherMadeChange() {}

void UserLettersAdder::receiveApplyClick()
{
    if (commandList_->executeCommand(setUserLetters_))
        emit changeMade();
}

void UserLettersAdder::reveiveTextChanged(const ScrabbleString&)
{
    emit focusIntercepted();
    showUserLettersView_->execute();
}
