#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual bool execute() = 0;
};

#endif // ICOMMAND_HPP
