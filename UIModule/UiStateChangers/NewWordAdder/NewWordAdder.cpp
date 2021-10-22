#include "NewWordAdder.hpp"

NewWordAdder::NewWordAdder(std::shared_ptr<ISwitch> orientationSwitch, std::shared_ptr<IScrabbleTextEdit> textEdit,
                           std::shared_ptr<ICommand> showWordFromTextEdit, std::shared_ptr<IReversableCommand> applyChanges,
                           std::shared_ptr<ICommandListManager> commandsList)
    :orientationSwitch_(orientationSwitch), textEdit_(textEdit), showWordFromTextEdit_(showWordFromTextEdit), applyChanges_(applyChanges), commandsList_(commandsList)
{
    connect(orientationSwitch_.get(), &ISwitch::stateChanged, this, &NewWordAdder::receiveSwitchChange);
    connect(textEdit_.get(), &IScrabbleTextEdit::textChanged, this, &NewWordAdder::receiveTextChange);
    orientationSwitch_->changeState(1);
}

void NewWordAdder::lostFocus()
{
    textEdit_->setText(ScrabbleString());
    showWordFromTextEdit_->execute();
}

void NewWordAdder::otherMadeChange() {}

void NewWordAdder::receiveApplyClick()
{
    showWordFromTextEdit_->execute();
    commandsList_->executeCommand(applyChanges_);
    textEdit_->setText({});
    emit changeMade();
}

void NewWordAdder::receiveGameBoardSelectionChange()
{
    if (textEdit_->getText().empty())
        return;

    emit focusIntercepted();
    showWordFromTextEdit_->execute();
}

void NewWordAdder::receiveSwitchChange()
{
    emit focusIntercepted();
    showWordFromTextEdit_->execute();
}

void NewWordAdder::receiveTextChange()
{
    emit focusIntercepted();
    showWordFromTextEdit_->execute();
}
