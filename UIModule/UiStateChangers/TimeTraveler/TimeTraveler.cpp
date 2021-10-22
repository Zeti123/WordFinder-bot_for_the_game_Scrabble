#include "TimeTraveler.hpp"

TimeTraveler::TimeTraveler(QPushButton& undoButton, QPushButton& redoButton, std::shared_ptr<ICommandListManager> commandsList,
                           std::unique_ptr<QShortcut>&& undoShortcut, std::unique_ptr<QShortcut>&& redoShortcut)
    :undoButton_(undoButton), redoButton_(redoButton), commandsList_(commandsList), undoShortcut_(std::move(undoShortcut)), redoShortcut_(std::move(redoShortcut))
{
    connect(&undoButton_, &QPushButton::clicked, this, &TimeTraveler::receiveUndoRequest);
    connect(&redoButton_, &QPushButton::clicked, this, &TimeTraveler::receiveRedoRequest);
    QObject::connect(undoShortcut_.get(), &QShortcut::activated, this, &TimeTraveler::receiveUndoRequest);
    QObject::connect(redoShortcut_.get(), &QShortcut::activated, this, &TimeTraveler::receiveRedoRequest);
    setEnabledOnButtons();
}

void TimeTraveler::lostFocus() {}

void TimeTraveler::otherMadeChange()
{
    setEnabledOnButtons();
}

void TimeTraveler::setEnabledOnButtons()
{
    undoButton_.setEnabled(commandsList_->canUndo());
    redoButton_.setEnabled(commandsList_->canRedo());
}

void TimeTraveler::receiveUndoRequest()
{
    emit focusIntercepted();
    if (commandsList_->canUndo())
    {
        commandsList_->undoCommand();
        emit changeMade();
    }

    setEnabledOnButtons();
}

void TimeTraveler::receiveRedoRequest()
{
    emit focusIntercepted();
    if (commandsList_->canRedo())
    {
        commandsList_->redoCommand();
        emit changeMade();
    }

    setEnabledOnButtons();
}
