#include "EraseFromGameBoardCommand.hpp"

EraseFromGameBoardCommand::EraseFromGameBoardCommand(std::shared_ptr<IGameBoardDisplay> gameBoard)
    :gameBoard_(gameBoard), lastErasedTile_(), lastSelected_(0, 0) { }

bool EraseFromGameBoardCommand::execute()
{
    lastSelected_ = gameBoard_->getSelectedFiled();
    auto gameBoard = gameBoard_->getGameBoard();
    auto& selectedTile = gameBoard[lastSelected_.second][lastSelected_.first];

    if (selectedTile.valueType == GameBoardTile::ValueType::EMPTY)
        return false;

    lastErasedTile_ = selectedTile;
    selectedTile = GameBoardTile('\0', GameBoardTile::ValueType::EMPTY);

    gameBoard_->updateGameBoard(gameBoard);
    return true;
}

void EraseFromGameBoardCommand::undo()
{
    auto gameBoard = gameBoard_->getGameBoard();
    auto& selectedTile = gameBoard[lastSelected_.second][lastSelected_.first];
    selectedTile = lastErasedTile_;

    gameBoard_->updateGameBoard(gameBoard);
}

void EraseFromGameBoardCommand::redo()
{
    auto gameBoard = gameBoard_->getGameBoard();
    auto& selectedTile = gameBoard[lastSelected_.second][lastSelected_.first];
    selectedTile = GameBoardTile('\0', GameBoardTile::ValueType::EMPTY);

    gameBoard_->updateGameBoard(gameBoard);
}

std::shared_ptr<IReversableCommand> EraseFromGameBoardCommand::copy()
{
    return std::make_shared<EraseFromGameBoardCommand>(*this);
}
