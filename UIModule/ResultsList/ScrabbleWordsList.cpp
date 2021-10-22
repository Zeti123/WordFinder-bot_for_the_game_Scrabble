#include "ScrabbleWordsList.hpp"

#include <algorithm>

ScrabbleWordsList::ScrabbleWordsList(QListWidget &list, std::shared_ptr<ILettersRenumberer> renumberer)
    :list_(list), lastSelected_(WordPlacement({}, {}, {}), 0), renumberer_(renumberer), sortedResults_({}), filteredEnd_(sortedResults_.begin()),
     comparator_([](const ScrabbleSearchEngineResult& l, const ScrabbleSearchEngineResult& r) { return l.score > r.score; }),
     filter_([](const ScrabbleSearchEngineResult&){ return true; })
{
    connect(&list_, &QListWidget::currentRowChanged, this, &ScrabbleWordsList::receiveCurrentRowChanged);
    connect(&list_, &QListWidget::itemDoubleClicked, this, &ScrabbleWordsList::receiveItemDoubleClicked);
}

std::size_t ScrabbleWordsList::size() const
{
    return filteredEnd_ - sortedResults_.begin();
}

const ScrabbleSearchEngineResult& ScrabbleWordsList::operator[](std::size_t index) const
{
    if (index < sortedResults_.size())
        return sortedResults_[index];

    std::runtime_error(std::string("index out of range in: ") + __func__);
}

void ScrabbleWordsList::sortResults(ComparatorFunctionType comparator)
{
    if (!sortedResults_.empty())
        std::sort(sortedResults_.begin(), filteredEnd_, comparator);
    comparator_ = comparator;
    refreshList();
}

void ScrabbleWordsList::filterResults(FilterFunctionType filter)
{
    filteredEnd_ = std::partition(sortedResults_.begin(), sortedResults_.end(), filter);

    filter_ = filter;
    sortResults(comparator_);
    refreshList();
}

void ScrabbleWordsList::setResults(const std::vector<ScrabbleSearchEngineResult>& results)
{
    sortedResults_ = results;
    filterResults(filter_);
}

void ScrabbleWordsList::setResults(std::vector<ScrabbleSearchEngineResult>&& results)
{
    sortedResults_ = std::move(results);
    filterResults(filter_);
}

ScrabbleSearchEngineResult ScrabbleWordsList::getSelected()
{
    return lastSelected_;
}

void ScrabbleWordsList::receiveCurrentRowChanged(int currentRow)
{
    if (clear_)
        return;

    lastSelected_ = this->operator[](currentRow);
    emit selectionChanged(this->operator[](currentRow));
}

void ScrabbleWordsList::receiveItemDoubleClicked(QListWidgetItem* item)
{
    if (clear_)
        return;

    int row = item->listWidget()->row(item);
    emit selectionDoubleClick(sortedResults_[row]);
}

void ScrabbleWordsList::refreshList()
{
    clear_ = true;
    list_.clear();
    clear_ = false;
    for (std::size_t i = 0; i < std::min(50ul, size()); i++)
    {
        list_.addItem(QString::fromStdWString(convertToReadable(sortedResults_[i].word.word)));
    }
    for (int i = 0; i < list_.count(); i++)
        list_.item(i)->setData(Qt::UserRole + 1, QString::fromStdString(std::to_string(sortedResults_[i].score)));
}

std::wstring ScrabbleWordsList::convertToReadable(const ScrabbleString& str)
{
    std::wstring ret;
    ret.reserve(str.size());
    for (auto letter: str)
    {
        ret.push_back(renumberer_->getLetterFromNum(letter.letter));
    }
    return ret;
}

