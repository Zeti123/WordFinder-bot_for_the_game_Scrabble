#include "SetUserLettersCommand.hpp"

SetUserLettersCommand::SetUserLettersCommand(std::shared_ptr<IUserLettersDisplay> userLettersDisplay, std::shared_ptr<IScrabbleTextEdit> userLettersTextEdit)
    :userLettersDisplay_(userLettersDisplay), userLettersTextEdit_(userLettersTextEdit), before_(), after_() {}

bool SetUserLettersCommand::execute()
{
    before_ = userLettersDisplay_->getUserLetters();
    after_ = dataTypeFromScrabbleString(userLettersTextEdit_->getText());
    if (before_ == after_)
        return false;

    userLettersDisplay_->setUserLetters(after_);
    return true;
}

void SetUserLettersCommand::undo()
{
    userLettersDisplay_->setUserLetters(before_);
}

void SetUserLettersCommand::redo()
{
    userLettersDisplay_->setUserLetters(after_);
}

std::shared_ptr<IReversableCommand> SetUserLettersCommand::copy()
{
    return std::make_shared<SetUserLettersCommand>(*this);
}

IUserLettersDisplay::DataType SetUserLettersCommand::dataTypeFromScrabbleString(const ScrabbleString& str)
{
    IUserLettersDisplay::DataType letters;

    for (std::size_t i = 0; i < str.size(); i++)
        letters[i] = str[i];

    return letters;
}
