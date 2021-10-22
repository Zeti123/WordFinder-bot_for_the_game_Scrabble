#ifndef UPDATEGAMEBOARDCOMMAND_HPP
#define UPDATEGAMEBOARDCOMMAND_HPP

#include "IGameBoardDisplay.hpp"
#include "ICommand.hpp"
#include "IScrabbleTextEdit.hpp"
#include "ISwitch.hpp"

#include <memory>

class PutWordOnGameBoardCommand: public ICommand
{
public:
    PutWordOnGameBoardCommand(std::shared_ptr<IGameBoardDisplay> gameBoard, std::shared_ptr<IScrabbleTextEdit> textEdit, std::shared_ptr<ISwitch> orientationSwitch);
    bool execute() override;

private:
    std::shared_ptr<IGameBoardDisplay> gameBoard_;
    std::shared_ptr<IScrabbleTextEdit> textEdit_;
    std::shared_ptr<ISwitch> orientationSwitch_;
};

#endif // UPDATEGAMEBOARDCOMMAND_HPP
