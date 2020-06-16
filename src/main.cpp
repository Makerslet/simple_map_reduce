#include "args_parser.h"

int main(int argc, char** argv)
{
    args_parser parser;
    auto result = parser.parse(argc, argv);
    if(!result.has_value())
        return 0;

    return 0;
}
