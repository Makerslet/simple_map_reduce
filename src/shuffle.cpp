#include "shuffle.h"
#include "utils.h"

shuffle::shuffle(int num_mappers, int num_reducers,
                 map_containers_ptr m_containers,
                 shuffle_containers_ptr s_containers) :
    base_executor(num_mappers),
    _num_reducers(num_reducers),
    _map_containers(m_containers),
    _shuffle_containers(s_containers)
{}


std::size_t shuffle::reduce_index(const std::string& line)
{
    return _hasher(line) % _num_reducers;
}

void shuffle::worker(int index)
{
    map_container& map_contr = _map_containers->at(index);

    for (const auto& line : map_contr)
    {
        std::size_t index = reduce_index(line);
        _shuffle_containers->at(index).insert(line);
    }
}
