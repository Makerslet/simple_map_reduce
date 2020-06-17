#include "map.h"

#include <fstream>
#include <climits>

map::map(const std::string& data_file_name, const offsets& offs,
         int num_threads, map_containers_ptr containers) :
    base_executor(num_threads),
    _data_file_name(data_file_name),
    _offsets(offs.begin(), offs.end()),
    _map_containers(containers)
{}


void map::worker(int index)
{
    map_functor functor;

    uintmax_t min_offset = _offsets[index];
    uintmax_t max_offset = static_cast<size_t>(index) + 1 < _offsets.size() ? _offsets[index + 1] : ULLONG_MAX;

    std::ifstream file(_data_file_name);
    file.seekg(min_offset);

    std::string line;
    map_container& container = _map_containers->at(index);

    while(std::getline(file, line) &&
          (max_offset == ULLONG_MAX || static_cast<uintmax_t>(file.tellg()) <= max_offset))
    {
        if(line.length() > 0 && line[line.length() - 1] == '\r')
            line = line.substr(0, line.length() - 1);

        functor.add_line(line);
    }

    for(const std::string& line : functor())
        container.insert(line);
}
