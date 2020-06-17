#include "args_parser.h"
#include "yamr.h"
#include "utils.h"

#include <iostream>

int main(int argc, char** argv)
{
    args_parser parser;
    auto result = parser.parse(argc, argv);
    if(!result.has_value())
        return 0;

    try {
        auto offsets = split_file(result->data_file, result->num_mappers);
        yamr executor(result->data_file, offsets, result->num_mappers, result->num_reducers);
        executor.exec();
    }
    catch(const std::runtime_error& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
