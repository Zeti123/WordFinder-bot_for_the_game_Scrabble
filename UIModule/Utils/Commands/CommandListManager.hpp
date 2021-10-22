#ifndef COMMANDLISTMANAGER_HPP
#define COMMANDLISTMANAGER_HPP

#include "ICommandListManager.hpp"

#include <vector>

class CommandListManager: public ICommandListManager
{
public:
    bool executeCommand(std::shared_ptr<IReversableCommand> command) override;
    bool undoCommand() override;
    bool redoCommand() override;
    bool canUndo() override;
    bool canRedo() override;

private:
    std::vector<std::shared_ptr<IReversableCommand>> prevCommands_;
    std::vector<std::shared_ptr<IReversableCommand>> nextCommands_;
};

#endif // COMMANDLISTMANAGER_HPP
