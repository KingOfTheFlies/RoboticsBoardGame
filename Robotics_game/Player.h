#pragma once

#include "Robot.h"
#include "Field.h"

#include <vector>

class Player {
public:
	Player(int index, int robots_num, Field *field) : index_(index), robots_num_(robots_num), field_(field) {
		CreateRobots();
		robots_alive = robots_num;
	}

	bool CreateRobots();

	bool MakeMove();

protected:
	int index_;
	std::vector<Robot> robots;
	int robots_alive;
	bool move_status = false;
	int robots_num_;
	Field* field_;
};

