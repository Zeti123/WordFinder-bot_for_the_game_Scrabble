#ifndef ILIST_HPP
#define ILIST_HPP

#include "AlgorithmModule/ScrabbleSearchEngineResult.hpp"

#include <QObject>

class IList: public QObject
{
    Q_OBJECT

public:
    using ComparatorFunctionType = std::function<bool(const ScrabbleSearchEngineResult&, const ScrabbleSearchEngineResult&)>;
    using FilterFunctionType = std::function<bool(const ScrabbleSearchEngineResult&)>;

    virtual std::size_t size() const = 0;
    virtual const ScrabbleSearchEngineResult& operator[](std::size_t) const = 0;
    virtual void sortResults(ComparatorFunctionType comparator) = 0;
    virtual void filterResults(FilterFunctionType filter) = 0;
    virtual void setResults(const std::vector<ScrabbleSearchEngineResult>& results) = 0;
    virtual void setResults(std::vector<ScrabbleSearchEngineResult>&& results) = 0;
    virtual ScrabbleSearchEngineResult getSelected() = 0;

signals:
    void selectionChanged(ScrabbleSearchEngineResult selectedResult);
    void selectionDoubleClick(ScrabbleSearchEngineResult selectionResult);
};

#endif // ILIST_HPP
