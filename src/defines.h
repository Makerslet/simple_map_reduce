#ifndef DEFINES_H
#define DEFINES_H

#include <set>
#include <vector>
#include <memory>
#include <mutex>

using offsets = std::set<unsigned long long>;

using map_container = std::multiset<std::string>;
using map_containers = std::vector<map_container>;
using map_containers_ptr = std::shared_ptr<map_containers>;

class shuffle_container
{
public:
    shuffle_container(){}
    void insert(const std::string& line)
    {
        std::lock_guard lock(_mutex);
        _lines.insert(line);
    }
    const std::multiset<std::string>& data(){return _lines;}

private:
    std::mutex _mutex;
    std::multiset<std::string> _lines;
};


using shuffle_containers = std::vector<shuffle_container>;
using shuffle_containers_ptr = std::shared_ptr<shuffle_containers>;

#endif // DEFINES_H
