#pragma once
#include "AbstractModel.h"
#include "PlayersFactory.h"

#include <list>

class PlayersFactoryCreate : public AbstractEvent {
public:
    PlayersFactoryCreate() {};
    PlayersFactoryCreate(int players_num, int robots_num, Field* field);
    void runEvent(std::list<AbstractObject*>& objects, TimeSpan time_span) override;
    PlayersFactory* GetPlayersFactory();
protected:
    PlayersFactory pf;
};

