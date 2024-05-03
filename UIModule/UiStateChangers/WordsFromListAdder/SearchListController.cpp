#include "SearchListController.hpp"

SearchListController::SearchListController(std::shared_ptr<IScrabbleTextEdit> searchBar, std::shared_ptr<IList> listOfWords, std::shared_ptr<ICommand> showResultFromGameBoardCommand,
                                           std::shared_ptr<IReversableCommand> applyChangesCommand, std::shared_ptr<ICommandListManager> commandsList)
    :searchBar_(searchBar), listOfWords_(listOfWords), showResultFromGameBoardCommand_(showResultFromGameBoardCommand),
     applyChangesCommand_(applyChangesCommand), commandsList_(commandsList)
{
    connect(listOfWords_.get(), &IList::selectionChanged, this, &SearchListController::receiveClick);
    connect(listOfWords_.get(), &IList::selectionDoubleClick, this, &SearchListController::receiveDoubleClick);
}

void SearchListController::lostFocus()
{
    QSignalBlocker(this);
    searchBar_->setText(ScrabbleString());
}

void SearchListController::otherMadeChange() {}

void SearchListController::receiveApply()
{
    listOfWords_->filterResults(getSearchFilter(searchBar_->getText()));
}

IList::FilterFunctionType SearchListController::getSearchFilter(const ScrabbleString& text)
{
    return [text](const ScrabbleSearchEngineResult& result) -> bool
    {
        if (text.size() == 0)
            return true;

        uint8_t textIndex = 0;
        const auto& word = result.word.word;
        for (uint8_t i = 0; i < word.size(); i++)
        {
            if (word[i].letter == text[textIndex].letter)
                textIndex++;
            if (textIndex == text.size())
                return true;
        }
        return false;
    };
}

void SearchListController::receiveClick()
{
    emit focusIntercepted();
    showResultFromGameBoardCommand_->execute();
}

void SearchListController::receiveDoubleClick()
{
    commandsList_->executeCommand(applyChangesCommand_);
    emit changeMade();
}
