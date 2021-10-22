#ifndef SEARCHLISTCONTROLLER_HPP
#define SEARCHLISTCONTROLLER_HPP

#include "IUiStateChanger.hpp"
#include "IScrabbleTextEdit.hpp"
#include "IList.hpp"
#include "IReversableCommand.hpp"
#include "ICommandListManager.hpp"

#include <memory>

class SearchListController: public IUiStateChanger
{
    Q_OBJECT

public:
    SearchListController(std::shared_ptr<IScrabbleTextEdit> searchBar, std::shared_ptr<IList> listOfWords, std::shared_ptr<ICommand> showResultFromGameBoardCommand,
                         std::shared_ptr<IReversableCommand> applyChangesCommand, std::shared_ptr<ICommandListManager> commandsList);
    void lostFocus() override;
    void otherMadeChange() override;

public slots:
    void receiveApply();

private:
    IList::FilterFunctionType getSearchFilter(const ScrabbleString& text);
    std::shared_ptr<IScrabbleTextEdit> searchBar_;
    std::shared_ptr<IList> listOfWords_;
    std::shared_ptr<ICommand> showResultFromGameBoardCommand_;
    std::shared_ptr<IReversableCommand> applyChangesCommand_;
    std::shared_ptr<ICommandListManager> commandsList_;

private slots:
    void receiveClick();
    void receiveDoubleClick();
};

#endif // SEARCHLISTCONTROLLER_HPP
