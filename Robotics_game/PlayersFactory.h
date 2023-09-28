#pragma once
#include "PlayersFactory.h"
#include "IpException.h"
#include "Field.h"
#include "Player.h"

#include <vector>

class PlayersFactory : public AbstractObject {
public:
    PlayersFactory() {};
    std::pair<TimeSpan, AbstractEvent*> getNearestEvent(std::list<AbstractObject*> objects) override;
    void update(TimeSpan time_span) override;

    void SetConfiguration(int players_num, int robots_num, Field* field);

    std::vector<Player>& GetPlayers();

protected:
    bool CreatePlayers();

	int players_num_ = 0;
	int robots_num_ = 0;
	Field* field_ = nullptr;
    std::vector<Player> players = {};
};
