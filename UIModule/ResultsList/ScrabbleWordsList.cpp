#include "ScrabbleWordsList.hpp"

#include <algorithm>
#include <execution>

Q_DECLARE_METATYPE(std::vector<ScrabbleSearchEngineResult>*)

ScrabbleWordsList::ScrabbleWordsList(QListView &list, std::shared_ptr<ILettersRenumberer> renumberer)
    :list_(list), lastSelected_(WordPlacement({}, {}, {}), 0),
     renumberer_(renumberer), sortedResults_({}), filteredEnd_(sortedResults_.begin()),
     comparator_([](const ScrabbleSearchEngineResult& l, const ScrabbleSearchEngineResult& r) { return l.score > r.score; }),
     filter_([](const ScrabbleSearchEngineResult&){ return true; })
{
    connect(list_.selectionModel(), &QItemSelectionModel::currentChanged, this, &ScrabbleWordsList::receiveCurrentRowChanged);
    connect(&list_, &QListView::clicked, this, &ScrabbleWordsList::receiveCurrentRowChanged);
    connect(&list_, &QListView::doubleClicked, this, &ScrabbleWordsList::receiveItemDoubleClicked);

    list_.model()->setData({}, QVariant::fromValue(&sortedResults_), Qt::EditRole);
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
        std::sort(std::execution::par, sortedResults_.begin(), filteredEnd_, comparator);
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

void ScrabbleWordsList::setResults(std::vector<ScrabbleSearchEngineResult>&& results)
{
    sortedResults_ = std::move(results);
    filterResults(filter_);

    refreshList();
}

ScrabbleSearchEngineResult ScrabbleWordsList::getSelected()
{
    return lastSelected_;
}

void ScrabbleWordsList::receiveCurrentRowChanged(const QModelIndex& current)
{
    lastSelected_ = this->operator[](current.row());
    emit selectionChanged(this->operator[](current.row()));
}

void ScrabbleWordsList::receiveItemDoubleClicked(const QModelIndex& current)
{
    emit selectionDoubleClick(sortedResults_[current.row()]);
}

void ScrabbleWordsList::refreshList()
{
    list_.model()->setData({}, {}, Qt::DisplayRole);
}

