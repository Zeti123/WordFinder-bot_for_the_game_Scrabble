#include "TrieSearchAlgorithm.hpp"
#include "SearchAlgorithmResult.hpp"
#include "log.hpp"

#include <random>
#include <iostream>
#include <future>

TrieSearchAlgorithm::PossibleLettersContainter::PossibleLettersContainter(bool isAllLettersPossible, const std::vector<char>& possibleLetters)
    : isAllLettersPossible_(isAllLettersPossible), possibleLetters_(possibleLetters) { }

void TrieSearchAlgorithm::PossibleLettersContainter::add(char letter)
{
    logger::debug("TrieSearchAlgorithm::PossibleLettersContainter(", letter, ")\n");
    possibleLetters_.push_back(letter);
}

void TrieSearchAlgorithm::PossibleLettersContainter::setAllLettersAsPossible(bool isAllLettersPossible)
{
    logger::debug("TrieSearchAlgorithm::PossibleLettersContainter::setAllLettersAsPossible(", isAllLettersPossible_, ")\n");
    isAllLettersPossible_ = isAllLettersPossible;
}

bool TrieSearchAlgorithm::PossibleLettersContainter::isLetterPossible(char letter) const
{
    logger::debug("TrieSearchAlgorithm::PossibleLettersContainter::isLetterPossible(", letter, ")\n");
    if (isAllLettersPossible_)
        return true;
    
    std::size_t size = possibleLetters_.size();
    for (std::size_t i = 0; i < size; i++)
        if (possibleLetters_[i] == letter)
            return true;
    
    return false;
}

bool TrieSearchAlgorithm::PossibleLettersContainter::isAllLettersPossible() const
{
    logger::debug("TrieSearchAlgorithm::PossibleLettersContainter::isAllLettersPossible()\n");
    return isAllLettersPossible_;
}

std::unique_ptr<TrieSearchAlgorithm> TrieSearchAlgorithm::Instance(const Trie& trie, const ThreadInformer& informer)
{
    logger::debug("TrieSearchAlgorithm instance created");
    return std::unique_ptr<TrieSearchAlgorithm>(new TrieSearchAlgorithm(trie, informer));
}

TrieSearchAlgorithm::TrieSearchAlgorithm(const Trie& trie, const ThreadInformer& informer)
    :trie_(trie), informer_(informer) { }

std::optional<TrieNode> TrieSearchAlgorithm::findWordEndNode(TrieNode node, const std::string& word) const
{
    logger::debug("TrieSearchAlgorithm::findWordEndNode(", node.character(), ' ', word, ")\n");
    for (auto letter: word)
    {
        auto index = node.getChildNum(letter);
        if (index == TrieNode::npos)
            return std::nullopt;
        
        node = node.childAt(index);
    }
    return node;
}

bool TrieSearchAlgorithm::searchSufix(TrieNode node, const std::string& sufix) const
{
    logger::debug("TrieSearchAlgorithm::searchSufix(", node.character(), ' ', sufix, ")\n");
    auto optionalNode = findWordEndNode(node, sufix);
    if (optionalNode == std::nullopt)
        return false;
    auto nodeRes = *optionalNode;

    return nodeRes.endOfWord();
}

TrieSearchAlgorithm::PossibleLettersContainter 
    TrieSearchAlgorithm::findPossibleLettersBetween(const std::string& prefix, const std::string& sufix) const
{
    logger::debug("TrieSearchAlgorithm::findPossibleLettersBetween(", prefix, ' ', sufix, ")\n");
    PossibleLettersContainter res;
    res.setAllLettersAsPossible(prefix == "" && sufix == "");

    auto node = trie_.root();
    auto optionalNode = findWordEndNode(node, prefix);
    if (optionalNode == std::nullopt)
        return res;
    
    node = *optionalNode;

    for (std::size_t i = 0; i < node.childCount(); i++)
    {
        if (searchSufix(node.childAt(i), sufix))
            res.add(node.childAt(i).character());
    }

    return res;
}

TrieSearchAlgorithm::RowOfPossibleLetters 
    TrieSearchAlgorithm::findPossibleLettersForRow(const GameBoard& gameBoard, uint8_t lineNumber) const
{
    logger::debug("TrieSearchAlgorithm::findPossibleLettersForRow(", gameBoard, ' ', lineNumber, ")\n");
    RowOfPossibleLetters res;
    for (uint8_t i = 0; i < GameBoard::size; i++)
    {
        auto prefix = scrabbleStrToStdStr(gameBoard.findPrefixForPos(std::make_pair(i, lineNumber)));
        auto sufix = scrabbleStrToStdStr(gameBoard.findSufixForPos(std::make_pair(i, lineNumber)));

        res[i] = findPossibleLettersBetween(prefix, sufix);
    }

    return res;
}

bool TrieSearchAlgorithm::isResultPlaceEndValid(const LineType& line, std::size_t index) const
{
    logger::debug("TrieSearchAlgorithm::isResultPlaceEndValid(", line, " ", index, ")\n");
    return (index + 1 == GameBoard::size) || (line[index + 1].valueType == GameBoardTile::ValueType::EMPTY);
}

void TrieSearchAlgorithm::searchRecursive(std::vector<TrieSearchAlgorithm::LineSearchResult>& result, 
                     ScrabbleString& currWord, const LineType& line, const TrieNode& node, 
                     std::size_t index, std::array<uint8_t, 257>& lettersBuff, int8_t minLen,
                     const RowOfPossibleLetters& possibleLetters, bool letterPlaced) const
{ 
    logger::debug("TrieSearchAlgorithm::searchRecursive(", currWord, " ", line, " ", index, " ", static_cast<int>(minLen), ")\n");
    if (node.endOfWord() && isResultPlaceEndValid(line, index - 1) && letterPlaced && minLen <= 0)
    {
        result.emplace_back(currWord, index - currWord.size());
        logger::debug("(TrieSearchAlgorithm::isResultPlaceEndValid) Result Find! ", currWord, " ", index, "\n");
    }
 
    // the next node would go off the board
    if (index >= GameBoard::size)
        return;

    // not empty field on board
    if (line[index].valueType != GameBoardTile::ValueType::EMPTY)
    {
        auto letterOnBoard = line[index];
        auto childNum = node.getChildNum(letterOnBoard.value);

        // doesn't have to check if node.childAt(childNum).subtreeSize >= minLen because it's always true in case of not empty tile on board 
        if (childNum != TrieNode::npos)
        {
            auto type = letterOnBoard.valueType == GameBoardTile::ValueType::NORMAL_TILE ? 
                ScrabbleLetter::Type::NORMAL_TILE : ScrabbleLetter::Type::EMPTY_TILE;

            currWord.push_back(ScrabbleLetter(letterOnBoard.value, type));
            searchRecursive(result, currWord, line, node.childAt(childNum), index + 1, lettersBuff, minLen - 1, possibleLetters, letterPlaced);
            currWord.pop_back();
        }
        return;
    }

    // empty field on board
    for (std::size_t i = 0; i < node.childCount(); i++)
    {
        if (static_cast<int32_t>(node.childAt(i).subtreeSize()) < minLen)
            continue;

        auto letter = node.childAt(i).character();

        if (!possibleLetters[index].isLetterPossible(letter))
            continue;

        if (lettersBuff[letter] > 0)
        {
            lettersBuff[letter]--;
            currWord.push_back(ScrabbleLetter(letter, ScrabbleLetter::Type::NORMAL_TILE));
            searchRecursive(result, currWord, line, node.childAt(i), index + 1, lettersBuff, minLen - 1, possibleLetters, true);
            currWord.pop_back();
            lettersBuff[letter]++;
        }
        else if (lettersBuff[EMPTY_TILE_CODE] > 0)
        {
            lettersBuff[EMPTY_TILE_CODE]--;
            currWord.push_back(ScrabbleLetter(letter, ScrabbleLetter::Type::EMPTY_TILE));
            searchRecursive(result, currWord, line, node.childAt(i), index + 1, lettersBuff, minLen - 1, possibleLetters, true);
            currWord.pop_back();
            lettersBuff[EMPTY_TILE_CODE]++;
        }
    }
}

std::array<uint8_t, 257> TrieSearchAlgorithm::makeLettersBuffer(const ScrabbleString& letters) const
{
    logger::debug("TrieSearchAlgorithm::makeLettersBuffer(", letters, ")\n");
    std::array<uint8_t, 257> buff = {};
    for (const auto& l: letters)
        if (l.type == ScrabbleLetter::Type::EMPTY_TILE)
            buff[EMPTY_TILE_CODE]++;
        else
            buff[l.letter]++;
    
    return buff;
}


// calculate minimal word lenght for every start position in line
MinSizeLineType TrieSearchAlgorithm::findMinLenForWords(const GameBoard& board, std::size_t index) const
{
    logger::debug("TrieSearchAlgorithm::findMinLenForWords(", board, ' ', index, ")\n");
    std::array<std::size_t, GameBoard::size> minLen = {};
    std::size_t lastNotEmpty = GameBoard::size + 1;
    bool isLastEmpty = true;
    for (int i = GameBoard::size - 1; i >= 0; i--)
    {
        if (board[index][i].valueType != GameBoardTile::ValueType::EMPTY && isLastEmpty == true)
            lastNotEmpty = i;

        else if (index > 0 && board[index - 1][i].valueType != GameBoardTile::ValueType::EMPTY && isLastEmpty == true)
            lastNotEmpty = i;

        else if (index + 1 < GameBoard::size && board[index + 1][i].valueType != GameBoardTile::ValueType::EMPTY && isLastEmpty == true)
            lastNotEmpty = i;

        minLen[i] = lastNotEmpty - i + 1;
        isLastEmpty = board[index][i].valueType == GameBoardTile::ValueType::EMPTY;
    }
    return minLen;
}

bool TrieSearchAlgorithm::isIndexValidForSearching(const LineType& line, std::size_t index) const
{
    logger::debug("TrieSearchAlgorithm::isIndexValidForSearching(", line, ' ', index, ")\n");
    return (index == 0) || (line[index - 1].valueType == GameBoardTile::ValueType::EMPTY);
}

std::vector<TrieSearchAlgorithm::LineSearchResult> TrieSearchAlgorithm::searchOneLine(const LineType& line, 
                                                                       const std::array<std::size_t, GameBoard::size>& minLen, 
                                                                       const ScrabbleString& letters,
                                                                       const RowOfPossibleLetters& possibleLetters) const
{
    logger::debug("TrieSearchAlgorithm::searchOneLine(", line, minLen, letters, ")\n");
    std::vector<TrieSearchAlgorithm::LineSearchResult> result;
    ScrabbleString word;
    std::array<uint8_t, 257> lettersBuff = makeLettersBuffer(letters);
    for (std::size_t i = 0; i + 1 < GameBoard::size; i++)
    {
        if (informer_.isNotified())
            return {};

        if (isIndexValidForSearching(line, i))
            searchRecursive(result, word, line, trie_.root(), i, lettersBuff, minLen[i], possibleLetters, false);
    }
    return result;
}

std::vector<SearchAlgorithmResult> TrieSearchAlgorithm::convertLineResult(std::vector<TrieSearchAlgorithm::LineSearchResult>&& lineResult, 
                                                                           Orientation orientation, uint8_t line) const
{
    logger::debug("TrieSearchAlgorithm::convertLineResult(", lineResult, static_cast<std::size_t>(orientation), line, ")\n");
    std::vector<SearchAlgorithmResult> result;
    result.reserve(lineResult.size());

    for (auto& r: lineResult)
    {
        if (orientation == Orientation::HORIZONTAL)
            result.emplace_back(std::move(r.word), std::make_pair(r.index, line), orientation);
        else
            result.emplace_back(std::move(r.word), std::make_pair(line, r.index), orientation);
    }

    return result;
}

void TrieSearchAlgorithm::searchLines(const SearchAlgorithmQuery& query, Orientation orientation,
                                      std::array<std::vector<SearchAlgorithmResult>, GameBoard::size * 2>& lineResults,
                                      std::size_t from, std::size_t to)
{
    if (orientation == Orientation::HORIZONTAL)
    {
        // search horizontally
        for (std::size_t i = from; i < to; i++)
        {
            auto possibleLettersInLine = findPossibleLettersForRow(query.gameBoard, i);
            logger::debug("(TrieSearchAlgorithm::search) Possible letters for line ", i, " ", query.gameBoard[i], ": ", possibleLettersInLine, "\n");
            auto lineResult = searchOneLine(query.gameBoard[i], findMinLenForWords(query.gameBoard, i), query.userLetters, possibleLettersInLine);
            lineResults[i] = convertLineResult(std::move(lineResult), Orientation::HORIZONTAL, i);
        }
    }
    else
    {
        // search vertically
        auto reflectedGameBoard = GameBoard::reflectGameBoard(query.gameBoard);
        for (std::size_t i = from; i < to; i++)
        {
            auto possibleLettersInLine = findPossibleLettersForRow(reflectedGameBoard, i);
            logger::debug("(TrieSearchAlgorithm::search) Possible letters for line ", i, " ", reflectedGameBoard[i], ": ", possibleLettersInLine, "\n");
            auto lineResult = searchOneLine(reflectedGameBoard[i], findMinLenForWords(reflectedGameBoard, i), query.userLetters, possibleLettersInLine);
            lineResults[i + GameBoard::size] = convertLineResult(std::move(lineResult), Orientation::VERTICAL, i);
        }
    }
}

#define THREAD

std::vector<SearchAlgorithmResult> TrieSearchAlgorithm::search(const SearchAlgorithmQuery& query)
{
    logger::debug("TrieSearchAlgorithm::Starting searching\n");
    std::vector<SearchAlgorithmResult> results;
    
    if (query.gameBoard.isEmpty())
    {
        logger::debug("board empty searching words only in the middle\n");

        LineType line;
        std::array<std::size_t, GameBoard::size> minLen = {{8, 7, 6, 5, 4, 3, 2, 1, 15, 15, 15, 15, 15, 15, 15}};
        RowOfPossibleLetters possibleLetters = {{}};

        auto lineResult = searchOneLine(line, minLen, query.userLetters, possibleLetters);
        auto lineResultCpy = lineResult;

        auto horizontalResults = convertLineResult(std::move(lineResult), Orientation::HORIZONTAL, 7);
        auto verticalResults = convertLineResult(std::move(lineResultCpy), Orientation::VERTICAL, 7);

        horizontalResults.insert(horizontalResults.end(), verticalResults.begin(), verticalResults.end());

        return horizontalResults;
    }

    std::array<std::vector<SearchAlgorithmResult>, GameBoard::size * 2> lineResults; 

    if (informer_.isNotified())
        return {};


#ifdef THREAD
    auto w1 = std::async(std::launch::async, &TrieSearchAlgorithm::searchLines, this, query, Orientation::HORIZONTAL, std::ref(lineResults), 0, GameBoard::size/2);
    auto w2 = std::async(std::launch::async, &TrieSearchAlgorithm::searchLines, this, query, Orientation::VERTICAL, std::ref(lineResults), 0, GameBoard::size/2);
    auto w3 = std::async(std::launch::async, &TrieSearchAlgorithm::searchLines, this, query, Orientation::HORIZONTAL, std::ref(lineResults), GameBoard::size/2, GameBoard::size);
    auto w4 = std::async(std::launch::async, &TrieSearchAlgorithm::searchLines, this, query, Orientation::VERTICAL, std::ref(lineResults), GameBoard::size/2, GameBoard::size);

    w1.wait();
    w2.wait();
    w3.wait();
    w4.wait();
#else
    searchLines(query, Orientation::HORIZONTAL, lineResults, 0, GameBoard::size);
    searchLines(query, Orientation::VERTICAL, lineResults, 0, GameBoard::size);
#endif

    searchLines(query, Orientation::VERTICAL, lineResults, 0, GameBoard::size);

    // merge results
    for (auto& res: lineResults)
        results.insert(results.end(), res.begin(), res.end());

    return results;
}

TrieSearchAlgorithm::LineSearchResult::LineSearchResult(const ScrabbleString& word, std::size_t index)
    :word(word), index(index) { }

std::ostream& operator << (std::ostream& o, const TrieSearchAlgorithm::LineSearchResult& res)
{
    o << '(' << res.word << ", " << static_cast<std::size_t>(res.index) << ")\n";
    return o;
}

std::ostream& operator << (std::ostream& o, const TrieSearchAlgorithm::PossibleLettersContainter& res)
{
    o << res.isAllLettersPossible() << res.possibleLetters_;
    return o;
}
