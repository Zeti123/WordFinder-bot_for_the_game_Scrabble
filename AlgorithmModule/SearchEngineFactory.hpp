#pragma once

#include "IScrabbleSearchEngine.hpp"

#include <memory>

#include "LettersInfo.hpp"
#include "ThreadInformer.hpp"

class SearchEngineFactory
{
public:
    static std::unique_ptr<IScrabbleSearchEngine> create(const std::vector<std::string>& listOfWords,
                                                         const LettersInfo& lettersInfo,
                                                         const ThreadInformer& threadInformer);
};
