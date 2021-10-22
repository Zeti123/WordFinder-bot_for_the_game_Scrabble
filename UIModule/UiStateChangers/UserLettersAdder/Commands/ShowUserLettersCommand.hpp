#ifndef SHOWUSERLETTERSCOMMAND_HPP
#define SHOWUSERLETTERSCOMMAND_HPP

#include "ICommand.hpp"
#include "IUserLettersDisplay.hpp"
#include "IScrabbleTextEdit.hpp"

#include <memory>

class ShowUserLettersCommand: public ICommand
{
public:
    ShowUserLettersCommand(std::shared_ptr<IUserLettersDisplay> userLettersDisplay, std::shared_ptr<IScrabbleTextEdit> userLettersTextEdit);
    bool execute() override;

private:
    std::shared_ptr<IUserLettersDisplay> userLettersDisplay_;
    std::shared_ptr<IScrabbleTextEdit> userLettersTextEdit_;
};

#endif // SHOWUSERLETTERSCOMMAND_HPP
