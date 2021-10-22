#ifndef SCRABBLEWORDSLIST_HPP
#define SCRABBLEWORDSLIST_HPP

#include "IList.hpp"
#include "ILettersRenumberer.hpp"

#include <memory>

#include <QListWidget>

class ScrabbleWordsList: public IList
{
    Q_OBJECT
public:
    ScrabbleWordsList(QListWidget& list, std::shared_ptr<ILettersRenumberer> renumberer);
    std::size_t size() const override;
    const ScrabbleSearchEngineResult& operator [](std::size_t index) const override;
    void sortResults(ComparatorFunctionType comparator) override;
    void filterResults(FilterFunctionType filter) override;
    void setResults(const std::vector<ScrabbleSearchEngineResult>& results) override;
    void setResults(std::vector<ScrabbleSearchEngineResult>&& results) override;
    ScrabbleSearchEngineResult getSelected() override;

private slots:
    void receiveCurrentRowChanged(int currentRow);
    void receiveItemDoubleClicked(QListWidgetItem* item);

private:
    bool clear_;
    void refreshList();
    std::wstring convertToReadable(const ScrabbleString& str);
    QListWidget& list_;
    ScrabbleSearchEngineResult lastSelected_;
    std::shared_ptr<ILettersRenumberer> renumberer_;
    std::vector<ScrabbleSearchEngineResult> sortedResults_;
    std::vector<ScrabbleSearchEngineResult>::iterator filteredEnd_;
    ComparatorFunctionType comparator_;
    FilterFunctionType filter_;
};

#endif // SCRABBLEWORDSLIST_HPP
