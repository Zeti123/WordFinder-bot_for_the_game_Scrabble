#include "UserLettersModel.hpp"

int UserLettersModel::rowCount(const QModelIndex&) const
{
    return 1;
}

int UserLettersModel::columnCount(const QModelIndex&) const
{
    return 7;
}

QVariant UserLettersModel::data(const QModelIndex& index, int role) const
{
    if (static_cast<std::size_t>(index.column()) < userLetters_.size())
        return QVariant::fromValue(std::optional<ScrabbleLetter>(userLetters_[index.column()]));

    throw std::runtime_error(std::string("index ") + std::to_string(index.column()) + " out of range in: " + __func__ + " in " + typeid(decltype(this)).name());
}

Qt::ItemFlags UserLettersModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool UserLettersModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        userLetters_[index.column()] = qvariant_cast<std::optional<ScrabbleLetter>>(value);
        return true;
    }
    else if (role == Qt::DisplayRole)
    {
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}
