#include "PutAndSaveWordOnGameBoardCommand.hpp"

PutAndSaveWordOnGameBoardCommand::PutAndSaveWordOnGameBoardCommand(std::shared_ptr<IGameBoardDisplay> gameBoard, std::shared_ptr<IScrabbleTextEdit> textEdit,
                                                           std::shared_ptr<ISwitch> orientationSwitch)
    :gameBoard_(gameBoard), textEdit_(textEdit), orientationSwitch_(orientationSwitch), lastSelected_({}, {}, {}), prevTiles_() { }

bool PutAndSaveWordOnGameBoardCommand::execute()
{
    Orientation orientation = orientationSwitch_->getState() ? Orientation::HORIZONTAL : Orientation::VERTICAL;
    std::pair<uint8_t, uint8_t> position = gameBoard_->getSelectedFiled();
    ScrabbleString word = textEdit_->getText();

    auto gameBoard = gameBoard_->getGameBoard();
    lastSelected_ = WordPlacement(word, position, orientation);
    prevTiles_ = gameBoard.getWordFromPlacement(lastSelected_);

    gameBoard.placeWord(lastSelected_);
    gameBoard_->updateGameBoard(gameBoard);

    return !word.empty();
}

void PutAndSaveWordOnGameBoardCommand::undo()
{
    auto gameBoard = gameBoard_->getGameBoard();
    gameBoard.placeWord(prevTiles_, lastSelected_.position, lastSelected_.orientation);
    gameBoard_->updateGameBoard(gameBoard);
}

void PutAndSaveWordOnGameBoardCommand::redo()
{
    auto gameBoard = gameBoard_->getGameBoard();
    gameBoard.placeWord(lastSelected_);
    gameBoard_->updateGameBoard(gameBoard);
}

std::shared_ptr<IReversableCommand> PutAndSaveWordOnGameBoardCommand::copy()
{
    return std::make_shared<PutAndSaveWordOnGameBoardCommand>(*this);
}
