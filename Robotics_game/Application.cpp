#include "Application.h"

bool Application::Parse(int argc, char** argv) {
    parser.Parse(argc, argv);
    return true;
}

bool Application::Configuration() {
    // TODO config field / players_factory
    pf = PlayersFactory(parser.GetNumOfPlayers(), parser.GetNumOfRobots(), &field);
    return true;
}

bool Application::Run(int argc, char** argv) {
    // TODO: run
    Parse(argc, argv);
}