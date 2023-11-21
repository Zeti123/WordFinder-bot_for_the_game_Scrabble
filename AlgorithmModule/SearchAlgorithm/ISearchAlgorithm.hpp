#pragma once

#include "SearchAlgorithmQuery.hpp"
#include "SearchAlgorithmResult.hpp"

#include <vector>

class  ISearchAlgorithm
{
public:
    virtual std::vector<SearchAlgorithmResult> search(const SearchAlgorithmQuery& query) = 0;
    virtual ~ISearchAlgorithm() = default;
};
