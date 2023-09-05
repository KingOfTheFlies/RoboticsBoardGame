#include "Application.h"

bool Application::Parse(int argc, char* argv[]) {
    parser.Parse(argc, argv);
    return true;
}

bool Application::Configuration(int argc, char* argv[]) {
    // TODO config field / players_factory
    Parse(argc, argv);
    fc = FieldCreate(parser.GetInputFileName());
    pf = PlayersFactory(parser.GetNumOfPlayers(), parser.GetNumOfRobots(), &field);
    return true;
}

bool Application::isEventListEmpty() {
    return event_list.size() == 0;
}

bool Application::addField() {
    addEvent(std::chrono::system_clock::now(), fc);
    return true;
}

bool Application::addPlayersFactory() {
    // addEvent(timespan, PlayersFactory obj) 
}

bool Application::Run() {
    // TODO: run
    return true;
}