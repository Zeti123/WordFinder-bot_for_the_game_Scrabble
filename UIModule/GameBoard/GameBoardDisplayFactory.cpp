#include "GameBoardDisplayFactory.hpp"

#include "GameBoardDelegate.hpp"
#include "TextureHandler.hpp"
#include "GameBoardModel.hpp"
#include "TableViewBasedGameBoard.hpp"

std::shared_ptr<IGameBoardDisplay> GameBoardDisplayFactory::create(QTableView& tableView,
                                                                   const std::shared_ptr<ITextureHandler>& textureHandler)
{
    auto model = new GameBoardModel({});
    tableView.setModel(model);
    tableView.setItemDelegate(new GameBoardDelegate(textureHandler, &tableView));
    tableView.setSelectionBehavior( QAbstractItemView::SelectItems );
    tableView.setSelectionMode( QAbstractItemView::SingleSelection );
    tableView.resize(58*15 + 2, 58*15 + 2);

    return std::make_shared<TableViewBasedGameBoard>(tableView);
}
