#pragma once
#include "IUiStateChanger.hpp"
#include "ISwitch.hpp"
#include "IScrabbleTextEdit.hpp"
#include "IReversableCommand.hpp"
#include "ICommandListManager.hpp"

#include <memory>

class NewWordAdder: public IUiStateChanger
{
    Q_OBJECT

public:
    NewWordAdder(std::shared_ptr<ISwitch> orientationSwitch, std::shared_ptr<IScrabbleTextEdit> textEdit, std::shared_ptr<ICommand> showWordFromTextEdit,
                 std::shared_ptr<IReversableCommand> applyChanges, std::shared_ptr<ICommandListManager> commandsList);
    void lostFocus() override;
    void otherMadeChange() override;

public slots:
    void receiveApplyClick();
    void receiveGameBoardSelectionChange();

private:
    std::shared_ptr<ISwitch> orientationSwitch_;
    std::shared_ptr<IScrabbleTextEdit> textEdit_;
    std::shared_ptr<ICommand> showWordFromTextEdit_;
    std::shared_ptr<IReversableCommand> applyChanges_;
    std::shared_ptr<ICommandListManager> commandsList_;

private slots:
    void receiveSwitchChange();
    void receiveTextChange();
};
