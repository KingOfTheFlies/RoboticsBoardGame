#include "CmdArgParser.h"

#include <iostream>
#include <string>

bool CmdArgParser::Parse(int argc, char** argv) {
    /*if (argc < MIN_QUANTITY_OF_COMMANDS) {
        IpException::ErrorCode errorCode = IpException::ErrorCode::IncorrectCmdInput;
        throw IpException(errorCode, "incorrect cmd input");
    }*/

    input_file = argv[1];
    output_file = argv[2];
    players_num = std::stoi(argv[3]);
    robots_num = std::stoi(argv[3]);            //TODO: exception

    return  true;
}