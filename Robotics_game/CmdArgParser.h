#pragma once

#include "IpException.h"

#include <string_view>
#include <vector>

 const int MIN_QUANTITY_OF_COMMANDS = 4;

class CmdArgParser {
public:

    bool Parse(int argc, char* argv[]);

    std::string_view GetInputFileName() const {
        return input_file;
    }

    std::string_view GetOutputFileName() const {
        return output_file;
    }
    int GetNumOfPlayers() const {
        return players_num;
    }

    int GetNumOfRobots() const {
        return robots_num;
    }

protected:
    std::string_view input_file;
    std::string_view output_file;
    int players_num;
    int robots_num;
};