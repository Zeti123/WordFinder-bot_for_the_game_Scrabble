#ifndef USERLETTERSMODEL_HPP
#define USERLETTERSMODEL_HPP

#include "ScrabbleString.hpp"

#include <optional>

#include <QAbstractItemModel>

Q_DECLARE_METATYPE(std::optional<ScrabbleLetter>)
class UserLettersModel: public QAbstractListModel
{
public:
    int rowCount(const QModelIndex&) const override;
    int columnCount(const QModelIndex&) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant& value, int role) override;

private:
    std::array<std::optional<ScrabbleLetter>, 7> userLetters_;
};
#endif // USERLETTERSMODEL_HPP
