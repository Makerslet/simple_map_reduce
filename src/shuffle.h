#ifndef SHUFFLE_H
#define SHUFFLE_H

#include "defines.h"
#include "base_executor.h"

#include <vector>

class shuffle : public base_executor
{
public:
    shuffle(int num_mappers, int num_reducers,
            map_containers_ptr m_containers,
            shuffle_containers_ptr s_containers);

private:
    std::size_t reduce_index(const std::string& line);
    void worker(int index);

private:
    int _num_reducers;
    map_containers_ptr _map_containers;
    shuffle_containers_ptr _shuffle_containers;
    std::hash<std::string> _hasher;
};

#endif // SHUFFLE_H
