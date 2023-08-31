#pragma once
#include "CmdArgParser.h"
#include "PlayersFactory.h"
#include "Field.h"

#include <iostream>

class Application {
public:
    bool Configuration();

    bool Run(int argc, char* argv[]);

    bool Parse(int argc, char* argv[]);
protected:
    PlayersFactory pf;
    CmdArgParser parser;
    Field field;
};