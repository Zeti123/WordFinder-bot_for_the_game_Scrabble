#include "Program.hpp"

Program::Program(std::unique_ptr<IUiController>&& uiController, std::unique_ptr<ScrabbleSearchEngine>&& searchEngine, const ThreadInformer& informer)
    :uiController_(std::move(uiController)), searchEngine_(std::move(searchEngine)), searchThread_(nullptr),
     stoppingThreadCondVar_(), threadShouldStop_(informer), threadStopped_(true)
{
    connect(uiController_.get(), &IUiController::gameStateChanged, this, &Program::receiveGameStateChanged);
    connect(this, &Program::threadDone, this, &Program::searchingEnd);
}

void Program::startSearch(GameBoard gameBoard, ScrabbleString userLetters)
{
    threadShouldStop_.reset();
    threadStopped_ = false;
    searchThread_ = std::unique_ptr<std::thread>(new std::thread(
    [this, gameBoard, userLetters]()
    {
        auto results = searchEngine_->search(ScrabbleSearchEngineQuery(gameBoard, userLetters));

        {
            std::lock_guard<std::mutex> lock(stoppingThreadMutex_);
            results_ = std::move(results);
            threadStopped_ = true;
        }
        stoppingThreadCondVar_.notify_one();
        emit threadDone();
    }));
    searchThread_->detach();
}

void Program::searchingEnd()
{
    uiController_->updateResults(std::move(results_));
}

void Program::gentlyAskTheThreadToEnd()
{
    {
        std::lock_guard<std::mutex> lock(stoppingThreadMutex_);
        threadShouldStop_.notify();
    }
    {
        std::unique_lock<std::mutex> lock(stoppingThreadMutex_);
        stoppingThreadCondVar_.wait(lock, [this]() -> bool { return threadStopped_; });
    }
}

void Program::receiveGameStateChanged(const GameState& gameState)
{
    uiController_->updateResults({});
    ScrabbleString userLetters = {};
    for (const auto& letter: gameState.userLetters)
        if (letter.has_value())
            userLetters += letter.value();
    gentlyAskTheThreadToEnd();
    startSearch(gameState.gameBoard, userLetters);
}

