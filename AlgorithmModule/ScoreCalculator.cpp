#include "ScoreCalculator.hpp"
#include "log.hpp"

std::unique_ptr<ScoreCalculator> ScoreCalculator::Instance(const LettersInfo& lettersInfo)
{
    logger::debug("ScoreCalucaltor instance created\n");
    return std::unique_ptr<ScoreCalculator>(new ScoreCalculator(lettersInfo));
}

bool ScoreCalculator::isNewWordCreated(const GameBoard& gameBoard, std::pair<uint8_t, uint8_t> position, Orientation orientation) const
{
    logger::debug("ScoreCalculator::isNewWordCreated(", gameBoard, ' ', static_cast<std::pair<std::size_t, std::size_t>>(position), ")\n");
    uint8_t posX = position.first;
    uint8_t posY = position.second;

    if (orientation == Orientation::HORIZONTAL)
        return (posY > 0 && gameBoard[posY][posX].valueType == GameBoardTile::ValueType::EMPTY && 
                gameBoard[posY - 1][posX].valueType != GameBoardTile::ValueType::EMPTY) || 
                (posY + 1 < GameBoard::size && gameBoard[posY][posX].valueType == GameBoardTile::ValueType::EMPTY && 
                gameBoard[posY + 1][posX].valueType != GameBoardTile::ValueType::EMPTY);
    
    return (posX > 0 && gameBoard[posY][posX].valueType == GameBoardTile::ValueType::EMPTY && 
                gameBoard[posY][posX - 1].valueType != GameBoardTile::ValueType::EMPTY) || 
                (posX + 1 < GameBoard::size && gameBoard[posY][posX].valueType == GameBoardTile::ValueType::EMPTY && 
                gameBoard[posY][posX + 1].valueType != GameBoardTile::ValueType::EMPTY);
}

std::vector<WordPlacement> ScoreCalculator::findAllCreatedWords(const WordPlacement& word, const GameBoard& gameBoard) const
{
    logger::debug("ScoreCalculator::findAllCreatedWords(", word, ' ', gameBoard, ")\n");
    std::vector<WordPlacement> words;
    words.emplace_back(word.word, word.position, word.orientation);
    GameBoard gameBoardTmp = gameBoard;
    for (std::size_t i = 0; i < word.word.size(); i++)
    {
        std::size_t posX = word.position.first + (word.orientation == Orientation::HORIZONTAL) * i;
        std::size_t posY = word.position.second + (word.orientation == Orientation::VERTICAL) * i;
        if (isNewWordCreated(gameBoard, std::make_pair(posX, posY), word.orientation))
        {
            gameBoardTmp[posY][posX] = word.word[i].type == ScrabbleLetter::Type::NORMAL_TILE ? 
                    GameBoardTile(word.word[i].letter, GameBoardTile::ValueType::NORMAL_TILE) : 
                    GameBoardTile(word.word[i].letter, GameBoardTile::ValueType::EMPTY_TILE);

            if (word.orientation == Orientation::HORIZONTAL)
                words.push_back(gameBoardTmp.findWordVerticallyCrossedBy(std::make_pair(posX, posY)));
            else
                words.push_back(gameBoardTmp.findWordHorizontallyCrossedBy(std::make_pair(posX, posY)));

            gameBoardTmp[posY][posX] = GameBoardTile('\0', GameBoardTile::ValueType::EMPTY);
        }
    }
    logger::debug(words.size() ," words have been found: ", words, '\n');
    return words;
}

std::size_t ScoreCalculator::calculateRawWordScore(const ScrabbleString& str) const
{
    logger::debug("ScoreCalculator::calculateRawWordScore(", str, ")\n");
    std::size_t score = 0;
    for (auto letter: str)
        if (letter.type == ScrabbleLetter::Type::NORMAL_TILE)
            score += lettersInfo_.getLetterScore(letter.letter);
    
    logger::debug("raw word score: ", score, '\n');
    return score;
}

std::size_t ScoreCalculator::calculateResultScore(const WordPlacement& word, const GameBoard& gameBoard) const
{
    logger::debug("ScoreCalculator::calculateResultScore(", word, ' ', gameBoard, ")\n");
    auto rawScore = calculateRawWordScore(word.word);
    std::size_t multiplier = 1;
    for (std::size_t i = 0; i < word.word.size(); i++)
    {
        uint8_t posX = word.position.first + (word.orientation == Orientation::HORIZONTAL) * i;
        uint8_t posY = word.position.second + (word.orientation == Orientation::VERTICAL) * i;

        if (gameBoard[posY][posX].valueType != GameBoardTile::ValueType::EMPTY)
            continue;

        auto bonus = GameBoard::getFieldBonus(posX, posY);
        auto letter = word.word[i];
        switch (bonus)
        {
        case FieldBonus::NONE:
            break; 
        case FieldBonus::LETTERX2:
            logger::debug("LETTER X2 bonus on letter: ", letter, '\n');
            rawScore += (letter.type == ScrabbleLetter::Type::NORMAL_TILE) ? lettersInfo_.getLetterScore(letter.letter) : 0;
            break;
        case FieldBonus::LETTERX3:
            logger::debug("LETTER X3 bonus on letter: ", letter, '\n');
            rawScore += ((letter.type == ScrabbleLetter::Type::NORMAL_TILE) ? lettersInfo_.getLetterScore(letter.letter) : 0) * 2;
            break;
        case FieldBonus::WORDX2:
            logger::debug("WORD X2 bonus on letter: ", letter, '\n');
            multiplier *= 2;
            break;
        case FieldBonus::WORDX3:
            logger::debug("WORD X3 bonus on letter: ", letter, '\n');
            multiplier *= 3;
            break;
        }
    }
    rawScore *= multiplier;
    logger::debug("result score: ", rawScore, '\n');
    return rawScore;
}

bool ScoreCalculator::isAllLettersUsed(const WordPlacement& word, const GameBoard& gameBoard) const
{
    logger::debug("ScoreCalculator::isAllLettersUsed(", word, ' ', gameBoard, ")\n");
    std::size_t usedLetters = 0;
    for (std::size_t i = 0; i < word.word.size(); i++)
    {
        uint8_t posX = word.position.first + (word.orientation == Orientation::HORIZONTAL) * i;
        uint8_t posY = word.position.second + (word.orientation == Orientation::VERTICAL) * i;
        if (gameBoard[posY][posX].valueType == GameBoardTile::ValueType::EMPTY) 
            usedLetters++;
    }
    if (usedLetters == 7)
        logger::debug("bonus for usage of 7 letters!\n");
    return usedLetters == 7;
}

std::vector<ScoreCalculatorResult> ScoreCalculator::calculateScores(const ScoreCalculatorQuery& query)
{
    logger::debug("ScoreCalculator::calculateScores(", query.gameBoard, ' ', query.words, ")\n");
    std::vector<ScoreCalculatorResult> results;
    for (const auto& res: query.words)
    {
        std::size_t score = 0;
        auto words = findAllCreatedWords(res, query.gameBoard);
        for (std::size_t i = 0; i < words.size(); i++)
        {
            const auto& word = words[i];
            score += calculateResultScore(WordPlacement(word.word, word.position, word.orientation), query.gameBoard);
        }
        if (isAllLettersUsed(res, query.gameBoard))
            score += 50;

        logger::debug("final score: ", score, '\n');
        results.push_back(ScoreCalculatorResult(res, score));
    }
    return results;
}

ScoreCalculator::ScoreCalculator(const LettersInfo& lettersInfo)
    :lettersInfo_(lettersInfo) { }