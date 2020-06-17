#include "utils.h"
#include "yamr.h"

yamr::yamr(const std::string& data_file_name, const offsets& offs,
           int num_mappers, int num_reducers):
    _data_file_name(data_file_name),
    _num_mappers(num_mappers),
    _num_reducers(num_reducers),
    _map_containers(std::make_shared<map_containers>(_num_mappers)),
    _shuffle_containers(std::make_shared<shuffle_containers>(_num_reducers)),
    _map(data_file_name, offs, num_mappers, _map_containers),
    _shuffle(num_mappers, num_reducers, _map_containers, _shuffle_containers),
    _reduce(num_reducers, _shuffle_containers)
{}

void yamr::exec()
{
    _map.exec();
    _shuffle.exec();
    _reduce.exec();
}

