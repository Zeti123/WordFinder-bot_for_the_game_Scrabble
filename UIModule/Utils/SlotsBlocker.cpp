#include "SlotsBlocker.hpp"

SlotsBlocker::SlotsBlocker(bool& slotBlocked)
    :oldValue_(slotBlocked), slotBlocked_(slotBlocked)
{
    slotBlocked_ = true;
}

SlotsBlocker::~SlotsBlocker()
{
    slotBlocked_ = oldValue_;
}
