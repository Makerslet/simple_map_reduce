#ifndef FUNCTORS_H
#define FUNCTORS_H

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

class map_functor
{
public:
    std::vector<std::string> operator() () const;

    void add_line(const std::string& line);

private:
    std::vector<std::string> _lines;
};

class reduce_functor
{
public:
    std::size_t operator() (const std::multiset<std::string>& lines);

private:
    std::unordered_map<std::string, int> _counters;
};

#endif // FUNCTORS_H
