#include "SearchEngineFactory.hpp"

#include "ScoreCalculatorFactory.hpp"
#include "SearchAlgorithmFactory.hpp"
#include "ScrabbleSearchEngine.hpp"

std::unique_ptr<IScrabbleSearchEngine> SearchEngineFactory::create(const std::vector<std::string>& listOfWords,
                                                                   const LettersInfo& lettersInfo,
                                                                   const ThreadInformer& threadInformer)
{
    return std::make_unique<ScrabbleSearchEngine>(SearchAlgorithmFactory::create(listOfWords, threadInformer),
                                                  ScoreCalculatorFactory::create(lettersInfo));
}
