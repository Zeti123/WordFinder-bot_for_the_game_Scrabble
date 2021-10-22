#include "GameBoardTilesEraser.hpp"

GameBoardTilesEraser::GameBoardTilesEraser(std::shared_ptr<ISwitch> onOffswitch, std::shared_ptr<IReversableCommand> eraseCommand, std::shared_ptr<ICommandListManager> commandsList)
    :onOffswitch_(onOffswitch), eraseCommand_(eraseCommand), commandsList_(commandsList)
{
    connect(onOffswitch_.get(), &ISwitch::stateChanged, this, &GameBoardTilesEraser::receiveSwitchChange);
}

void GameBoardTilesEraser::lostFocus()
{
    QSignalBlocker(this);
    onOffswitch_->changeState(false);
}

void GameBoardTilesEraser::otherMadeChange() {}

void GameBoardTilesEraser::receiveGameBoardSelectionChange()
{
    if (onOffswitch_->getState() == true)
        if (commandsList_->executeCommand(eraseCommand_))
            emit changeMade();
}

void GameBoardTilesEraser::receiveSwitchChange()
{
    emit focusIntercepted();
}
