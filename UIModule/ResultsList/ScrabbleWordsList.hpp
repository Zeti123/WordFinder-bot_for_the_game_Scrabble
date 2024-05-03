#pragma once

#include "IList.hpp"
#include "ILettersRenumberer.hpp"

#include <memory>

#include <QListView>

class ScrabbleWordsList: public IList
{
    Q_OBJECT

public:
    ScrabbleWordsList(QListView& list, std::shared_ptr<ILettersRenumberer> renumberer);
    std::size_t size() const override;
    const ScrabbleSearchEngineResult& operator [](std::size_t index) const override;
    void sortResults(ComparatorFunctionType comparator) override;
    void filterResults(FilterFunctionType filter) override;
    void setResults(std::vector<ScrabbleSearchEngineResult>&& results) override;
    ScrabbleSearchEngineResult getSelected() override;

private slots:
    void receiveCurrentRowChanged(const QModelIndex& current);
    void receiveItemDoubleClicked(const QModelIndex& current);

private:
    void refreshList();

    QListView& list_;
    ScrabbleSearchEngineResult lastSelected_;
    std::shared_ptr<ILettersRenumberer> renumberer_;
    std::vector<ScrabbleSearchEngineResult> sortedResults_;
    std::vector<ScrabbleSearchEngineResult>::iterator filteredEnd_;
    ComparatorFunctionType comparator_;
    FilterFunctionType filter_;
};
