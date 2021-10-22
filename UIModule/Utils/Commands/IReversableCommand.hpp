#ifndef ISERIALIZABLECOMMAND_HPP
#define ISERIALIZABLECOMMAND_HPP

#include "ICommand.hpp"

#include <memory>

class IReversableCommand: public ICommand
{
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual std::shared_ptr<IReversableCommand> copy() = 0;
};

#endif // ISERIALIZABLECOMMAND_HPP
