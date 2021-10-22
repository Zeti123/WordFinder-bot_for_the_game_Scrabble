#ifndef GAMEBOARDCONTROLLER_HPP
#define GAMEBOARDCONTROLLER_HPP

#include "IUiController.hpp"
#include "IReversableCommand.hpp"
#include "IUiStateChanger.hpp"
#include "IUserLettersDisplay.hpp"
#include "IList.hpp"

class UiController: public IUiController
{
    Q_OBJECT

public:
    UiController(std::shared_ptr<IGameBoardDisplay> gameBoardDisplay, std::shared_ptr<IUserLettersDisplay> userLettersDisplay,
                 std::shared_ptr<IList> searchListController, std::vector<std::shared_ptr<IUiStateChanger>> stateChangers);

    void addStateChanger(std::shared_ptr<IUiStateChanger> stateChanger);
    void removeStateChanger(std::shared_ptr<IUiStateChanger> stateChanger);
    void updateResults(const std::vector<ScrabbleSearchEngineResult>& results) override;
    void updateResults(std::vector<ScrabbleSearchEngineResult>&& results) override;

private:
    void receiveFocusChange(std::weak_ptr<IUiStateChanger> stateChanger);
    void receiveStateChange(std::weak_ptr<IUiStateChanger> stateChanger);
    std::shared_ptr<IGameBoardDisplay> gameBoardDisplay_;
    std::shared_ptr<IUserLettersDisplay> userLettersDisplay_;
    std::shared_ptr<IList> listOfWords_;
    std::weak_ptr<IUiStateChanger> currentStateChanger_;
    std::vector<std::shared_ptr<IUiStateChanger>> stateChangers_;

private slots:
    void receiveGameBoardChange(const GameBoard& gameBoard);
    void receiveUserLettersChange(const IUserLettersDisplay::DataType& userLetters);
};

#endif // GAMEBOARDCONTROLLER_HPP
