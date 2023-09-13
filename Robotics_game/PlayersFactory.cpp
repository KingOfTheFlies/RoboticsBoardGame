#include "PlayersFactory.h"

bool PlayersFactory::CreatePlayers() {
	for (int i = 0; i < players_num_; ++i) {
		players.push_back(Player(i, robots_num_, field_));
	}
    return true;
}
void PlayersFactory::SetConfiguration(int players_num, int robots_num, Field* field) {
    players_num_ = players_num;
    robots_num_ = robots_num;
    field_ = field;
    CreatePlayers();
}

void PlayersFactory::update(TimeSpan time_span) {
    return;
}

std::pair<TimeSpan, AbstractEvent*> PlayersFactory::getNearestEvent(std::list<AbstractObject*> objects) {
    return std::move(std::make_pair<TimeSpan, AbstractEvent*>(TimeSpan::max(), nullptr));
}