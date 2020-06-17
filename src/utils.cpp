#include "utils.h"

#include <boost/filesystem.hpp>

#include <cmath>
#include <fstream>
#include <iostream>

static uintmax_t prev_line_offset(uintmax_t offset, std::ifstream& fstream)
{
    if (offset == 0)
        return 0;

    char sym;
    fstream.seekg(offset);
    do
    {
        fstream.read(&sym, 1);
        fstream.seekg(-2, std::ios_base::cur);
    }
    while (sym != '\n' &&
           sym != '\r' &&
           fstream.tellg() > 0);

    if (fstream.tellg() == 0)
        return 0;

    fstream.seekg(1, std::ios_base::cur);
    return fstream.tellg();
}

offsets split_file(const std::string& data_file_name, int parts)
{
    if (!boost::filesystem::exists(data_file_name))
        throw std::runtime_error("input file does not exist");

    unsigned long long fileSize = boost::filesystem::file_size(data_file_name);
    unsigned long long partSize =
        static_cast<unsigned long long>(std::ceil(static_cast<double>(fileSize) / parts));

    offsets offs;
    std::ifstream fstream(data_file_name, std::ios::in | std::ios::binary);
    uintmax_t offset = 0;
    offs.emplace(offset);
    offset += partSize;

    while (offset < fileSize)
    {
        uintmax_t prevNewLineOffset = prev_line_offset(offset, fstream);

        fstream.seekg(prevNewLineOffset);
        char sym;
        do
        {
            fstream.read(&sym, 1);
        }
        while ((sym == '\n' || sym == '\r') &&
               fstream.tellg() < static_cast<long long>(fileSize));

        fstream.seekg(-1, std::ios_base::cur);

        auto result = offs.emplace(fstream.tellg());

        if (!result.second)
            throw std::runtime_error("zero size part");
        offset += partSize;
    }
    return offs;
}
