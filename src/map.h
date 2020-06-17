#ifndef MAP_H
#define MAP_H

#include "defines.h"
#include "functors.h"
#include "base_executor.h"

#include <vector>

class map : public base_executor
{
    using vector_ull = std::vector<unsigned long long>;
public:
    map(const std::string& data_file_name, const offsets& offs,
        int num_threads, map_containers_ptr containers);

private:
    void worker(int index);

private:
    std::string _data_file_name;
    vector_ull _offsets;
    map_containers_ptr _map_containers;
};

#endif // MAP_H
