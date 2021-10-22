#pragma once

#include "ISearchAlgorithm.hpp"
#include "IScoreCalculator.hpp"

#include <memory>

class ScrabbleSearchEngine
{
public:
    ScrabbleSearchEngine(std::unique_ptr<ISearchAlgorithm>&& searchAlgorithm, std::unique_ptr<IScoreCalculator>&& scoreCalculator);
    std::vector<ScrabbleSearchEngineResult> search(const ScrabbleSearchEngineQuery& query);

private:
    std::unique_ptr<ISearchAlgorithm> searchAlgorithm_;
    std::unique_ptr<IScoreCalculator> scoreCalculator_;
};
