#pragma once
#include "AbstractModel.h"
#include "CmdArgParser.h"
#include "PlayersFactory.h"
#include "Field.h"
#include "FieldCreate.h"

#include <iostream>

class Application : public AbstractWrapper {
public:
    bool Configuration(int argc, char* argv[]);

    bool Run();     // TODO

    bool Parse(int argc, char* argv[]);

    bool isEventListEmpty();

    bool addField();

    bool addPlayersFactory();

protected:
    PlayersFactory pf;
    CmdArgParser parser;
    Field field;
    FieldCreate fc;
};