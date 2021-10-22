#ifndef ICOMMANDLISTMANAGER_HPP
#define ICOMMANDLISTMANAGER_HPP

#include "IReversableCommand.hpp"

#include <memory>

class ICommandListManager
{
public:
    virtual bool executeCommand(std::shared_ptr<IReversableCommand> command) = 0;
    virtual bool undoCommand() = 0;
    virtual bool redoCommand() = 0;
    virtual bool canUndo() = 0;
    virtual bool canRedo() = 0;
};

#endif // ICOMMANDLISTMANAGER_HPP
