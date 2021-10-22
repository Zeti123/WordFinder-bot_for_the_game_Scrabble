#ifndef APPLYGAMEBOARDCHANGESCOMMAND_HPP
#define APPLYGAMEBOARDCHANGESCOMMAND_HPP

#include "ISwitch.hpp"
#include "IGameBoardDisplay.hpp"
#include "IReversableCommand.hpp"
#include "IScrabbleTextEdit.hpp"

#include "AlgorithmModule/ScrabbleSearchEngineResult.hpp"

class PutAndSaveWordOnGameBoardCommand: public IReversableCommand
{
public:
    PutAndSaveWordOnGameBoardCommand(std::shared_ptr<IGameBoardDisplay> gameBoard, std::shared_ptr<IScrabbleTextEdit> textEdit, std::shared_ptr<ISwitch> orientationSwitch);
    bool execute() override;
    void undo() override;
    void redo() override;
    std::shared_ptr<IReversableCommand> copy() override;

private:
    std::shared_ptr<IGameBoardDisplay> gameBoard_;
    std::shared_ptr<IScrabbleTextEdit> textEdit_;
    std::shared_ptr<ISwitch> orientationSwitch_;
    WordPlacement lastSelected_;
    std::vector<GameBoardTile> prevTiles_;
};

#endif // APPLYGAMEBOARDCHANGESCOMMAND_HPP
