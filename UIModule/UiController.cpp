#include "UiController.hpp"
#include "GameBoard.hpp"
#include "IGameBoardDisplay.hpp"

UiController::UiController(std::shared_ptr<IGameBoardDisplay> gameBoardDisplay, std::shared_ptr<IUserLettersDisplay> userLettersDisplay,
                           std::shared_ptr<IList> listOfWords, std::vector<std::shared_ptr<IUiStateChanger>> stateChangers)
    :gameBoardDisplay_(gameBoardDisplay), userLettersDisplay_(userLettersDisplay), listOfWords_(listOfWords),
     currentStateChanger_(), stateChangers_(stateChangers)
{
    connect(gameBoardDisplay_.get(), &IGameBoardDisplay::gameBoardChanged, this, &UiController::receiveGameBoardChange);
    connect(userLettersDisplay_.get(), &IUserLettersDisplay::userLettersChanged, this, &UiController::receiveUserLettersChange);
    for (auto& obj: stateChangers_)
    {
        std::weak_ptr<IUiStateChanger> weakPtr = obj;
        connect(obj.get(), &IUiStateChanger::focusIntercepted, this, [weakPtr, this](){ receiveFocusChange(weakPtr); });
        connect(obj.get(), &IUiStateChanger::changeMade, this, [weakPtr, this](){ receiveStateChange(weakPtr); });
    }
}

void UiController::addStateChanger(std::shared_ptr<IUiStateChanger> stateChanger)
{
    stateChangers_.push_back(stateChanger);
}

void UiController::removeStateChanger(std::shared_ptr<IUiStateChanger> stateChanger)
{
    auto it = std::find(stateChangers_.begin(), stateChangers_.end(), stateChanger);
    stateChangers_.erase(it);
}

void UiController::updateResults(const std::vector<ScrabbleSearchEngineResult>& results)
{
    listOfWords_->setResults(results);
}

void UiController::updateResults(std::vector<ScrabbleSearchEngineResult>&& results)
{
    listOfWords_->setResults(results);
}

void UiController::receiveFocusChange(std::weak_ptr<IUiStateChanger> stateChanger)
{
    auto ptr = stateChanger.lock();
    if (!ptr)
        std::runtime_error("bad state changer: already deleted!");

    if (ptr == currentStateChanger_.lock())
        return;

    currentStateChanger_ = stateChanger;
    for (auto& obj: stateChangers_)
    {
        QSignalBlocker blocker(obj.get());
        if (obj.get() != ptr.get())
            obj->lostFocus();
    }
}

void UiController::receiveStateChange(std::weak_ptr<IUiStateChanger> stateChanger)
{
    auto ptr = stateChanger.lock();
    if (!ptr)
        std::runtime_error("bad state changer: already deleted!");
    for (auto stateChangerPtr: stateChangers_)
        if (stateChangerPtr.get() != stateChanger.lock().get())
            stateChangerPtr->otherMadeChange();
}

void UiController::receiveGameBoardChange(const GameBoard& gameBoard)
{
    emit gameStateChanged({gameBoard, userLettersDisplay_->getUserLetters()});
}

void UiController::receiveUserLettersChange(const IUserLettersDisplay::DataType& userLetters)
{
    emit gameStateChanged({gameBoardDisplay_->getGameBoard(), userLetters});
}


