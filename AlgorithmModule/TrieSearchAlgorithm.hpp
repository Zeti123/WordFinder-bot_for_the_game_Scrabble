#pragma once

#include "ISearchAlgorithm.hpp"
#include "Trie.hpp"
#include "GameBoard.hpp"
#include "ScrabbleString.hpp"
#include "ThreadInformer.hpp"

#include <optional>
#include <memory>

using MinSizeLineType = std::array<std::size_t, GameBoard::size>;
constexpr size_t EMPTY_TILE_CODE = 256;

class TrieSearchAlgorithm: public ISearchAlgorithm
{
public:
    static std::unique_ptr<TrieSearchAlgorithm> Instance(const Trie& trie, const ThreadInformer& informer);
    std::vector<SearchAlgorithmResult> search(const SearchAlgorithmQuery& query) override;

private:
    struct LineSearchResult
    {
        LineSearchResult(const ScrabbleString& word, std::size_t index);
        ScrabbleString word;
        uint8_t index;
    };
    class PossibleLettersContainter
    {
        friend std::ostream& operator << (std::ostream& o, const PossibleLettersContainter& res);

    public:
        PossibleLettersContainter(bool isAllLettersPossible = true, const std::vector<char>& possibleLetters = {});
        void add(char letter);
        void setAllLettersAsPossible(bool isAllLettersPossible);
        bool isLetterPossible(char letter) const;
        bool isAllLettersPossible() const;

    private:
        bool isAllLettersPossible_;
        std::vector<char> possibleLetters_;
    };

    using RowOfPossibleLetters = std::array<PossibleLettersContainter, GameBoard::size>;

private:
    TrieSearchAlgorithm(const Trie& trie, const ThreadInformer& informer);
    void searchLines(const SearchAlgorithmQuery& query, Orientation orientation,
                     std::array<std::vector<SearchAlgorithmResult>, GameBoard::size * 2>& lineResults,
                     std::size_t from, std::size_t to);
    std::optional<TrieNode> findWordEndNode(TrieNode node, const std::string& word) const;
    bool searchSufix(TrieNode node, const std::string& sufix) const;
    PossibleLettersContainter findPossibleLettersBetween(const std::string& prefix, const std::string& sufix) const;
    RowOfPossibleLetters findPossibleLettersForRow(const GameBoard& gameBoard, uint8_t lineNumber) const;
    bool isResultPlaceEndValid(const LineType& line, std::size_t index) const;
    void searchRecursive(std::vector<TrieSearchAlgorithm::LineSearchResult>& result, ScrabbleString& currWord,
                     const LineType& line, const TrieNode& node, 
                     std::size_t index, std::array<uint8_t, 257>& lettersBuff, int8_t minLen,
                     const RowOfPossibleLetters& possibleLetters, bool letterPlaced) const;
    std::array<uint8_t, 257> makeLettersBuffer(const ScrabbleString& letters) const;
    MinSizeLineType findMinLenForWords(const GameBoard& board, std::size_t index) const;
    bool isIndexValidForSearching(const LineType& line, std::size_t index) const;
    std::vector<TrieSearchAlgorithm::LineSearchResult> searchOneLine(const LineType& line, 
                                                      const std::array<std::size_t, GameBoard::size>& minLen, 
                                                      const ScrabbleString& letters,
                                                      const RowOfPossibleLetters& possibleLetters) const;
    std::vector<SearchAlgorithmResult> convertLineResult(std::vector<TrieSearchAlgorithm::LineSearchResult>&& lineResult, 
                                                          Orientation orientation, uint8_t line) const;
    
    Trie trie_;
    ThreadInformer informer_;

    friend std::ostream& operator << (std::ostream& o, const TrieSearchAlgorithm::LineSearchResult& res);
    friend std::ostream& operator << (std::ostream& o, const PossibleLettersContainter& res);
};

std::ostream& operator << (std::ostream& o, const TrieSearchAlgorithm::LineSearchResult& res);
std::ostream& operator << (std::ostream& o, const TrieSearchAlgorithm::PossibleLettersContainter& res);
