#pragma once

#include "ISearchAlgorithm.hpp"

#include <memory>

#include "ThreadInformer.hpp"

class SearchAlgorithmFactory
{
public:
    static std::unique_ptr<ISearchAlgorithm> create(const std::vector<std::string>& listOfWords, const ThreadInformer& informer);
};
