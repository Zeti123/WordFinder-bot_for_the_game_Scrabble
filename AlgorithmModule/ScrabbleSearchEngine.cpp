#include "ScrabbleSearchEngine.hpp"

ScrabbleSearchEngine::ScrabbleSearchEngine(std::unique_ptr<ISearchAlgorithm>&& searchAlgorithm, 
                                           std::unique_ptr<IScoreCalculator>&& scoreCalculator)
    :searchAlgorithm_(std::move(searchAlgorithm)), scoreCalculator_(std::move(scoreCalculator)) { }

std::vector<ScrabbleSearchEngineResult> ScrabbleSearchEngine::search(const ScrabbleSearchEngineQuery& query)
{
    auto algorithmResults = searchAlgorithm_->search(query);
    auto results = scoreCalculator_->calculateScores(ScoreCalculatorQuery(query.gameBoard, algorithmResults));
    return results;
}