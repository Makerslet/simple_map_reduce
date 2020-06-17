#include "functors.h"

#include <string>

void map_functor::add_line(const std::string& line)
{
    for (std::size_t index = 1; index <= line.length(); ++index)
        _lines.push_back(line.substr(0, index));
}

std::vector<std::string> map_functor::operator() () const
{
    return _lines;
}

std::size_t reduce_functor::operator() (const std::multiset<std::string>& lines)
{
    std::size_t maxLength = 0;
    for (const std::string& line : lines)
    {
        int size = ++_counters[line];
        if (size > 1 && line.length() > maxLength)
        {
            maxLength = line.length();
        }
    }
    return maxLength + 1;
}



