#include "Player.h"

bool Player::CreateRobots() {
	for (int i = 0; i < robots_num_; ++i) {
		robots.push_back(Robot(i, field_));
	}
    return true;
}