#pragma once
#include "IUiStateChanger.hpp"
#include "ICommandListManager.hpp"
#include "IReversableCommand.hpp"
#include "ISwitch.hpp"

#include <memory>

#include <QPushButton>

class GameBoardTilesEraser: public IUiStateChanger
{
public:
    GameBoardTilesEraser(std::shared_ptr<ISwitch> onOffswitch, std::shared_ptr<IReversableCommand> eraseCommand, std::shared_ptr<ICommandListManager> commandsList);
    void lostFocus() override;
    void otherMadeChange() override;

public slots:
    void receiveGameBoardSelectionChange();
    void receiveSwitchChange();

private:
    std::shared_ptr<ISwitch> onOffswitch_;
    std::shared_ptr<IReversableCommand> eraseCommand_;
    std::shared_ptr<ICommandListManager> commandsList_;
};
