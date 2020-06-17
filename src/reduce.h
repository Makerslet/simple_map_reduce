#ifndef REDUCE_H
#define REDUCE_H

#include "defines.h"
#include "functors.h"
#include "base_executor.h"

class reduce : public base_executor
{
public:
    reduce(int num_reducers, shuffle_containers_ptr shuffle_containers);

private:
    void worker(int index);

private:
    shuffle_containers_ptr _shuffle_containers;
};

#endif // REDUCE_H
