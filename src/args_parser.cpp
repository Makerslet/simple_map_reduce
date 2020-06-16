#include "args_parser.h"

#include <iostream>

args_parser::args_parser() :
    _description("allowed options")
{
    _description.add_options()
            ("help", "input arguments description")
            ("input", bpo::value<std::string>(), "handled input file")
            ("mappers", bpo::value<int>(), "number of mapping threads")
            ("reducers", bpo::value<int>(), "number of reducing threads");
}

std::optional<parse_result> args_parser::parse(int argc, char **argv)
{
    std::optional<parse_result> result;
    try {
        auto parsed_options = boost::program_options::parse_command_line(argc, argv, _description);
        boost::program_options::store(parsed_options, _values_storage);

        if(_values_storage.count("help"))
        {
            std::cout << _description << std::endl;
            return result;
        }

        result = parse_result();
        if(!_values_storage.count("input"))
            throw std::logic_error("input file wasn't set");
        else
            result->data_file = _values_storage["input"].as<std::string>();

        if(!_values_storage.count("mappers"))
            throw std::logic_error("number of mappers wasn't set");
        else
        {
            int mappers = _values_storage["mappers"].as<int>();
            if(mappers < 0)
                throw std::logic_error("number of mappers can't have negative value");
            if(mappers == 0)
                throw std::logic_error("number of mappers can't have 0 value");
            if(mappers > 8)
                throw std::logic_error("number of mappers can't have value greater than 8");

            result->num_mappers = mappers;
        }

        if(!_values_storage.count("reducers"))
            throw std::logic_error("number of reducers wasn't set");
        else
        {
            int reducers = _values_storage["reducers"].as<int>();
            if(reducers < 0)
                throw std::logic_error("number of reducers can't have negative value");
            if(reducers == 0)
                throw std::logic_error("number of reducers can't have 0 value");
            if(reducers > 8)
                throw std::logic_error("number of reducers can't have value greater than 8");

            result->num_reducers = reducers;
        }
    }
    catch(const std::logic_error& ex)
    {
        std::cout << "error: " << ex.what() << std::endl;
        std::cout << _description;

        result.reset();
        return result;
    }

    return result;
}
