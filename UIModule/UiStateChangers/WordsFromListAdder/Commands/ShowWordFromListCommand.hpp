#pragma once

#include "ICommand.hpp"
#include "IList.hpp"
#include "IGameBoardDisplay.hpp"

#include <memory>

class ShowWordFromListCommand: public ICommand
{
public:
    ShowWordFromListCommand(std::shared_ptr<IGameBoardDisplay> display, std::shared_ptr<IList> list);
    bool execute() override;

private:
    std::shared_ptr<IGameBoardDisplay> display_;
    std::shared_ptr<IList> list_;
};
