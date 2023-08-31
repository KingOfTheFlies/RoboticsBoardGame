#include "PlayersFactory.h"

bool PlayersFactory::CreatePlayers() {
	for (int i = 0; i < players_num_; ++i) {
		players.push_back(Player(i, robots_num_, field_));
	}
}