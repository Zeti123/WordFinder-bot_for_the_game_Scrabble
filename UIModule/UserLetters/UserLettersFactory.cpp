#include "UserLettersFactory.hpp"

#include "UserLettersDelegate.hpp"
#include "UserLettersModel.hpp"
#include "ListViewBasedUserLetters.hpp"

std::shared_ptr<IUserLettersDisplay> UserLettersFactory::create(QTableView& listView, std::shared_ptr<ITextureHandler> textureHandler)
{
    listView.setItemDelegate(new UserLettersDelegate(textureHandler));
    listView.setModel(new UserLettersModel());
    return std::make_shared<ListViewBasedUserLetters>(listView);
}
