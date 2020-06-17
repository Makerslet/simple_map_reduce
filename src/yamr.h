#ifndef YAMR_H
#define YAMR_H

#include "map.h"
#include "shuffle.h"
#include "reduce.h"

class yamr
{
public:
    yamr(const std::string& data_file_name, const offsets& offs,
         int num_mappers, int num_reducers);
    void exec();

private:
    std::string _data_file_name;
    int _num_mappers;
    int _num_reducers;
    map_containers_ptr _map_containers;
    shuffle_containers_ptr _shuffle_containers;
    map _map;
    shuffle _shuffle;
    reduce _reduce;
};

#endif // YAMR_H
