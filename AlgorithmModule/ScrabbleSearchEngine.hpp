#pragma once

#include "IScrabbleSearchEngine.hpp"

#include "ISearchAlgorithm.hpp"
#include "IScoreCalculator.hpp"

#include <memory>

class ScrabbleSearchEngine: public IScrabbleSearchEngine
{
public:
    ScrabbleSearchEngine(std::unique_ptr<ISearchAlgorithm>&& searchAlgorithm, std::unique_ptr<IScoreCalculator>&& scoreCalculator);
    std::vector<ScrabbleSearchEngineResult> search(const ScrabbleSearchEngineQuery& query) override;

private:
    std::unique_ptr<ISearchAlgorithm> searchAlgorithm_;
    std::unique_ptr<IScoreCalculator> scoreCalculator_;
};
