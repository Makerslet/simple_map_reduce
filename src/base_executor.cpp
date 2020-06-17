#include "base_executor.h"

#include <iostream>

base_executor::base_executor(int num_threads) :
    _num_threads(num_threads)
{}

void base_executor::exec()
{
    for (int index = 0; index < _num_threads; ++index)
        _threads.emplace_back(std::thread(&base_executor::thread_proc, this, index));

    wait_threads();
}

void base_executor::wait_threads()
{
    for(auto& thread : _threads)
        thread.join();
}

void base_executor::thread_proc(int index)
{
    try {
        worker(index);
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
