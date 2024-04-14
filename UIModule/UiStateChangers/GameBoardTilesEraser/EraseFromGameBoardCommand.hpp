#pragma once

#include "IReversableCommand.hpp"
#include "IGameBoardDisplay.hpp"

class EraseFromGameBoardCommand: public IReversableCommand
{
public:
    EraseFromGameBoardCommand(std::shared_ptr<IGameBoardDisplay> gameBoard);
    bool execute() override;
    void undo() override;
    void redo() override;
    std::shared_ptr<IReversableCommand> copy() override;

private:
    std::shared_ptr<IGameBoardDisplay> gameBoard_;
    GameBoardTile lastErasedTile_;
    std::pair<uint8_t, uint8_t> lastSelected_;
};
