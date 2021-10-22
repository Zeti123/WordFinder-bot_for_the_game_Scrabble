#ifndef SETUSERLETTERSCOMMAND_HPP
#define SETUSERLETTERSCOMMAND_HPP

#include "IReversableCommand.hpp"
#include "IUserLettersDisplay.hpp"
#include "IScrabbleTextEdit.hpp"

class SetUserLettersCommand: public IReversableCommand
{
public:
    SetUserLettersCommand(std::shared_ptr<IUserLettersDisplay> userLettersDisplay, std::shared_ptr<IScrabbleTextEdit> userLettersTextEdit);
    bool execute() override;
    void undo() override;
    void redo() override;
    std::shared_ptr<IReversableCommand> copy() override;

private:
    IUserLettersDisplay::DataType dataTypeFromScrabbleString(const ScrabbleString& str);
    std::shared_ptr<IUserLettersDisplay> userLettersDisplay_;
    std::shared_ptr<IScrabbleTextEdit> userLettersTextEdit_;
    IUserLettersDisplay::DataType before_;
    IUserLettersDisplay::DataType after_;
};

#endif // SETUSERLETTERSCOMMAND_HPP
