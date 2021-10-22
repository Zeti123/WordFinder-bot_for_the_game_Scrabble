#ifndef TIMETRAVELER_HPP
#define TIMETRAVELER_HPP

#include "IUiStateChanger.hpp"
#include "ICommandListManager.hpp"

#include <QShortcut>
#include <QPushButton>

class TimeTraveler: public IUiStateChanger
{
    Q_OBJECT

public:
    TimeTraveler(QPushButton& undoButton, QPushButton& redoButton, std::shared_ptr<ICommandListManager> commandsList,
                 std::unique_ptr<QShortcut>&& undoShortcut, std::unique_ptr<QShortcut>&& redoShortcut);

    void lostFocus() override;
    void otherMadeChange() override;

private:
    void setEnabledOnButtons();
    QPushButton& undoButton_;
    QPushButton& redoButton_;
    std::shared_ptr<ICommandListManager> commandsList_;
    std::unique_ptr<QShortcut> undoShortcut_;
    std::unique_ptr<QShortcut> redoShortcut_;

private slots:
    void receiveUndoRequest();
    void receiveRedoRequest();
};

#endif // TIMETRAVELER_HPP
