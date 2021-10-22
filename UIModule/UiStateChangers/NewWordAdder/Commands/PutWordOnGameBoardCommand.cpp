#include "PutWordOnGameBoardCommand.hpp"

PutWordOnGameBoardCommand::PutWordOnGameBoardCommand(std::shared_ptr<IGameBoardDisplay> gameBoard, std::shared_ptr<IScrabbleTextEdit> textEdit, std::shared_ptr<ISwitch> orientationSwitch)
    :gameBoard_(gameBoard), textEdit_(textEdit), orientationSwitch_(orientationSwitch) { }

bool PutWordOnGameBoardCommand::execute()
{
    Orientation orientation = orientationSwitch_->getState() ? Orientation::HORIZONTAL : Orientation::VERTICAL;
    std::pair<uint8_t, uint8_t> position = gameBoard_->getSelectedFiled();
    ScrabbleString word = textEdit_->getText();
    gameBoard_->showResultView(WordPlacement(word, position, orientation));
    return !word.empty();
}

