#pragma once

#include "ScrabbleSearchEngineQuery.hpp"
#include "ScrabbleSearchEngineResult.hpp"

class IScrabbleSearchEngine
{
public:
    virtual std::vector<ScrabbleSearchEngineResult> search(const ScrabbleSearchEngineQuery& query) = 0;
};
