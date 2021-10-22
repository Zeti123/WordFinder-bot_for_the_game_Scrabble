#ifndef USERLETTERSADDER_HPP
#define USERLETTERSADDER_HPP

#include "IReversableCommand.hpp"
#include "IScrabbleTextEdit.hpp"
#include "IUiStateChanger.hpp"
#include "ICommandListManager.hpp"

#include <memory>

class UserLettersAdder: public IUiStateChanger
{
    Q_OBJECT

public:
    UserLettersAdder(std::shared_ptr<IScrabbleTextEdit> userLetters, std::shared_ptr<ICommand> showUserLettersView,
                     std::shared_ptr<IReversableCommand> setUserLetters, std::shared_ptr<ICommandListManager> commandList);
    void lostFocus() override;
    void otherMadeChange() override;

public slots:
    void receiveApplyClick();

private:
    std::shared_ptr<IScrabbleTextEdit> userLetters_;
    std::shared_ptr<ICommand> showUserLettersView_;
    std::shared_ptr<IReversableCommand> setUserLetters_;
    std::shared_ptr<ICommandListManager> commandList_;

private slots:
    void reveiveTextChanged(const ScrabbleString& scrabbleString);
};

#endif // USERLETTERSADDER_HPP
