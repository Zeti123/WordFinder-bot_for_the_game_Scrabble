#include "ResultsListsFactory.hpp"

#include <QScrollBar>

#include "ScrabbleWordsList.hpp"
#include "ListItemDelegate.hpp"

std::shared_ptr<IList> ResultsListsFactory::create(QListWidget& list, std::shared_ptr<ILettersRenumberer> renumberer)
{
    list.setItemDelegate(new ListItemDelegate(&list));
    list.verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"
                                                "border: 0px solid grey;"
                                                "background: #006f65;"
                                             "}"
                                             "QScrollBar::handle:vertical {"
                                                "background: #00a49a;"
                                                "min-height: 40px;"
                                             "}"
                                             "QScrollBar::add-line:vertical {"
                                                "border: none;"
                                                "background: none;"
                                             "}"
                                             "QScrollBar::sub-line:vertical {"
                                                "border: none;"
                                                "background: none;"
                                             "}");

    return std::make_shared<ScrabbleWordsList>(list, renumberer);
}
