#include "CommandListManager.hpp"

bool CommandListManager::executeCommand(std::shared_ptr<IReversableCommand> command)
{
    nextCommands_.clear();
    prevCommands_.push_back(command->copy());
    bool success = prevCommands_.back()->execute();
    if (!success)
        prevCommands_.pop_back();
    return success;
}

bool CommandListManager::undoCommand()
{
    if (!canUndo())
        return false;

    auto prevCommand = prevCommands_.back();
    prevCommands_.pop_back();
    nextCommands_.push_back(prevCommand);
    prevCommand->undo();
    return true;
}

bool CommandListManager::redoCommand()
{
    if (!canRedo())
        return false;

    auto nextCommand = nextCommands_.back();
    nextCommands_.pop_back();
    prevCommands_.push_back(nextCommand);
    nextCommand->redo();
    return true;
}

bool CommandListManager::canUndo()
{
    return prevCommands_.empty() == false;
}

bool CommandListManager::canRedo()
{
    return nextCommands_.empty() == false;
}
