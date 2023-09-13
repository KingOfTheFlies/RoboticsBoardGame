#include "PlayersFactoryCreate.h"

PlayersFactoryCreate::PlayersFactoryCreate(int players_num, int robots_num, Field* field) {
    pf.SetConfiguration(players_num, robots_num, field);
}

void PlayersFactoryCreate::runEvent(std::list<AbstractObject*>& objects, TimeSpan time_span) {
    pf.lastUpdated = time_span;
    objects.push_back(&pf);
    //pf.CreatePlayers();
}

PlayersFactory* PlayersFactoryCreate::GetPlayersFactory() {
    return &pf;
}