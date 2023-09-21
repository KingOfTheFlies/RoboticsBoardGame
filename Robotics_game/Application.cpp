#include "Application.h"

Application::Application(int argc, char* argv[]) {
    Configuration(argc, argv);
}

bool Application::Parse(int argc, char* argv[]) {
    parser.Parse(argc, argv);
    return true;
}

bool Application::IsThereAWinner() {
    return me.IsThereAWinner();
}

bool Application::Configuration(int argc, char* argv[]) {
    // TODO config field / players_factory
    Parse(argc, argv);
    fc = FieldCreate(parser.GetInputFileName());
    field = fc.GetField();
    pfc = PlayersFactoryCreate(parser.GetNumOfPlayers(), parser.GetNumOfRobots(), field);
    pf = pfc.GetPlayersFactory();
    me.SetPf(pf);
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
    addEvent(std::chrono::system_clock::now(), pfc);
    return true;
}

bool Application::addMoveEvent() {
    addEvent(std::chrono::system_clock::now(), me);
    return true;
}

bool Application::Run() {
    // TODO: run
    return true;
}