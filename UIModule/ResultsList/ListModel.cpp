#include "ListModel.hpp"

ListModel::ListModel()
    :columnCount_(0), resultsPtr_(nullptr) {}

int ListModel::rowCount(const QModelIndex& parent) const
{
    if (columnCount_ > resultsPtr_->size())
        return resultsPtr_->size();

    return columnCount_;
}

QVariant ListModel::headerData(int, Qt::Orientation, int) const
{
    return QString("");
}

QVariant ListModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (static_cast<size_t>(index.row()) < resultsPtr_->size())
            return QVariant::fromValue(resultsPtr_->at(index.row()));
    }
    return QVariant();
}

Qt::ItemFlags ListModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index);
}

bool ListModel::setData(const QModelIndex&, const QVariant& data, int role)
{
    if (role == Qt::EditRole)
    {
        resultsPtr_ = std::move(qvariant_cast<std::vector<ScrabbleSearchEngineResult>*>(data));
    }
    else if (role == Qt::DisplayRole)
    {
        columnCount_ = std::min(resultsPtr_->size(), DEFAULT_COLUMN_COUNT);
        emit dataChanged({}, {}, {role});
    }

    return true;
}

bool ListModel::canFetchMore(const QModelIndex& parent) const
{
    if (parent.isValid())
        return false;

    return (columnCount_ < resultsPtr_->size());
}

void ListModel::fetchMore(const QModelIndex& parent)
{
    if (parent.isValid())
        return;

    const int start = columnCount_;
    const int itemsToFetch = std::min(COLUMN_COUNT_INCREMENT, resultsPtr_->size());

    if (itemsToFetch <= 0)
        return;

    beginInsertRows(QModelIndex(), start, start + itemsToFetch - 1);

    columnCount_ += itemsToFetch;

    endInsertRows();
}
