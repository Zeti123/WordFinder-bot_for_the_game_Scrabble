#include "ShowWordFromListCommand.hpp"

ShowWordFromListCommand::ShowWordFromListCommand(std::shared_ptr<IGameBoardDisplay> display, std::shared_ptr<IList> list)
    :display_(display), list_(list) {}

bool ShowWordFromListCommand::execute()
{
    auto selected = list_->getSelected();
    display_->showResultView(selected.word);
    return true;
}
