#include "ThreadInformer.hpp"

ThreadInformer::ThreadInformer()
    :notified_(std::make_shared<volatile bool>(false)) { }

ThreadInformer::ThreadInformer(const ThreadInformer& other)
    :notified_(other.notified_) { }

void ThreadInformer::notify()
{
    *notified_ = true;
}

void ThreadInformer::reset()
{
    *notified_ = false;
}

bool ThreadInformer::isNotified() const
{
    return *notified_;
}
