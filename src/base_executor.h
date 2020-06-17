#ifndef BASE_EXECUTOR_H
#define BASE_EXECUTOR_H

#include <vector>
#include <thread>

class base_executor
{
    using threads = std::vector<std::thread>;
public:
    base_executor(int num_threads);
    void exec();

private:
    void wait_threads();
    void thread_proc(int index);

    virtual void worker(int index) = 0;

private:
    int _num_threads;
    threads _threads;
};

#endif // BASE_EXECUTOR_H
