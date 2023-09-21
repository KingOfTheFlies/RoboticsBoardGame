#pragma once
#include "AbstractModel.h"
#include "PlayersFactory.h"

enum WIN_CONSTS { MAX_POINTS_VAL = 15 };

class MoveEvent : public AbstractEvent{
public:
    MoveEvent() {};
    bool SetPf(PlayersFactory* players_factory);
    void runEvent(std::list<AbstractObject*>& objects, TimeSpan time_span) override;
    bool IsThereAWinner();
protected:
    bool there_is_a_winner = false;
    std::queue<Player*> players_q;
    PlayersFactory* pf_ptr = NULL;
};

