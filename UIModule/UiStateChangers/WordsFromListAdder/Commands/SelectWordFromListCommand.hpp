#pragma once

#include "IReversableCommand.hpp"
#include "IList.hpp"
#include "IGameBoardDisplay.hpp"

#include <memory>

class SelectWordFromListCommand: public IReversableCommand
{
public:
    SelectWordFromListCommand(std::shared_ptr<IGameBoardDisplay> display, std::shared_ptr<IList> list);
    bool execute() override;
    void undo() override;
    void redo() override;
    std::shared_ptr<IReversableCommand> copy() override;

private:
    void putLastSelectedOnBoard();
    void liftLastSelectedFromBoard();

    std::shared_ptr<IList> list_;
    std::shared_ptr<IGameBoardDisplay> display_;
    ScrabbleSearchEngineResult lastSelected_;
    std::vector<GameBoardTile> prevTiles_;
};

