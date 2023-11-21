#include "SelectWordFromListCommand.hpp"

SelectWordFromListCommand::SelectWordFromListCommand(std::shared_ptr<IGameBoardDisplay> display, std::shared_ptr<IList> list)
    :list_(list), display_(display), lastSelected_(WordPlacement({}, {}, {}), 0), prevTiles_() { }

bool SelectWordFromListCommand::execute()
{
    lastSelected_ = list_->getSelected();
    putLastSelectedOnBoard();
    return true;
}

void SelectWordFromListCommand::undo()
{
    liftLastSelectedFromBoard();
}

void SelectWordFromListCommand::redo()
{
    putLastSelectedOnBoard();
}

std::shared_ptr<IReversableCommand> SelectWordFromListCommand::copy()
{
    return std::make_shared<SelectWordFromListCommand>(*this);
}

void SelectWordFromListCommand::putLastSelectedOnBoard()
{
    auto gameBoard = display_->getGameBoard();
    prevTiles_ = gameBoard.getWordFromPlacement(lastSelected_.word);
    gameBoard.placeWord(lastSelected_.word);
    display_->updateGameBoard(gameBoard);
}

void SelectWordFromListCommand::liftLastSelectedFromBoard()
{
    auto gameBoard = display_->getGameBoard();
    gameBoard.placeWord(prevTiles_, lastSelected_.word.position, lastSelected_.word.orientation);
    display_->updateGameBoard(gameBoard);
}
