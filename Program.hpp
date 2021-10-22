#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "ThreadInformer.hpp"
#include "IUiController.hpp"

#include "AlgorithmModule/ScrabbleSearchEngineResult.hpp"
#include "AlgorithmModule/ScrabbleSearchEngine.hpp"

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include <QObject>

class Program: public QObject
{
    Q_OBJECT
public:
    Program(std::unique_ptr<IUiController>&& uiController, std::unique_ptr<ScrabbleSearchEngine>&& searchEngine, const ThreadInformer& informer);

private:
    void startSearch(GameBoard gameBoard, ScrabbleString userLetters);
    void gentlyAskTheThreadToEnd();
    std::unique_ptr<IUiController> uiController_;
    std::unique_ptr<ScrabbleSearchEngine> searchEngine_;
    std::vector<ScrabbleSearchEngineResult> results_;

    std::unique_ptr<std::thread> searchThread_;
    std::mutex stoppingThreadMutex_;
    std::condition_variable stoppingThreadCondVar_;
    ThreadInformer threadShouldStop_;
    volatile bool threadStopped_;

signals:
    void threadDone();

private slots:
    void searchingEnd();
    void receiveGameStateChanged(const GameState& gameState);
};

#endif // PROGRAM_HPP
