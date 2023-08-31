#pragma once
#include "Field.h"
#include "Player.h"

#include <vector>

class PlayersFactory {
public:
	PlayersFactory(int players_num, int robots_num, Field* field) : players_num_(players_num),
																	field_(field),
																	robots_num_(robots_num) {
		CreatePlayers();
		Start();
	};

	bool CreatePlayers();
	bool Start();	//TODO
protected:
	int players_num_;
	int robots_num_;
	Field* field_;
	std::vector<Player> players;
};
