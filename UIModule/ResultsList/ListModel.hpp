#pragma once

#include "ScrabbleSearchEngineResult.hpp"


#include <QAbstractListModel>


Q_DECLARE_METATYPE(ScrabbleSearchEngineResult)

// a little hack here, vector with results can be very long so to avoid copying it we pass pointer to whole vector using one setData
// original vector with results is stored in ScrabbleWrodsList
Q_DECLARE_METATYPE(std::vector<ScrabbleSearchEngineResult>*)

class ListModel: public QAbstractListModel
{
public:
    ListModel();
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant headerData(int, Qt::Orientation, int role = Qt::DisplayRole ) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex&, const QVariant& data, int role) override;
    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

private:
    constexpr static inline size_t DEFAULT_COLUMN_COUNT = 50;
    constexpr static inline size_t COLUMN_COUNT_INCREMENT = 1;

    size_t columnCount_;
    std::vector<ScrabbleSearchEngineResult>* resultsPtr_;
};

