#pragma once

#include <memory>

#include <QListWidget>

#include "IList.hpp"
#include "ILettersRenumberer.hpp"

class ResultsListsFactory
{
public:
    static std::shared_ptr<IList> create(QListView& list, std::shared_ptr<ILettersRenumberer> renumberer);
};
