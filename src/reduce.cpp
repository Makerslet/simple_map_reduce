#include "reduce.h"

#include <fstream>
#include <sstream>

reduce::reduce(int num_reducers,
               shuffle_containers_ptr shuffle_containers) :
    base_executor(num_reducers),
    _shuffle_containers(shuffle_containers)
{}


void reduce::worker(int index)
{
    shuffle_container& container = _shuffle_containers->at(index);
    std::stringstream fileName;
    fileName << "reducer_" << index;

    std::ofstream f(fileName.str());
    reduce_functor functor;
    f << functor(container.data());
}

