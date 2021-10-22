#ifndef THREADINFORMER_HPP
#define THREADINFORMER_HPP

#include <memory>

class ThreadInformer
{
public:
    ThreadInformer();
    ThreadInformer(const ThreadInformer& other);
    void notify();
    void reset();
    bool isNotified() const;

private:
    std::shared_ptr<volatile bool> notified_;
};

#endif // THREADINFORMER_HPP
