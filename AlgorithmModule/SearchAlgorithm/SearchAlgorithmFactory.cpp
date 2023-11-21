#include "SearchAlgorithmFactory.hpp"

#include "TrieSearchAlgorithm.hpp"
#include "Trie.hpp"

std::unique_ptr<ISearchAlgorithm> SearchAlgorithmFactory::create(const std::vector<std::string>& listOfWords, const ThreadInformer& informer)
{
    return TrieSearchAlgorithm::Instance(Trie(listOfWords), informer);
}
