#ifndef SLOTSBLOCKER_HPP
#define SLOTSBLOCKER_HPP


class SlotsBlocker
{
public:
    SlotsBlocker(bool& slotBlocked);
    ~SlotsBlocker();

private:
    bool oldValue_;
    bool& slotBlocked_;
};

#endif // SLOTSBLOCKER_HPP
