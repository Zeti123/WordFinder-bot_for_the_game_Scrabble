#pragma once

#include <memory>

#include <QListWidget>

#include "IList.hpp"
#include "ILettersRenumberer.hpp"

class ResultsListsFactory
{
public:
    std::shared_ptr<IList> create(QListWidget& list, std::shared_ptr<ILettersRenumberer> renumberer);
};
