#pragma once

#include "Robot.h"
#include "Field.h"

#include <vector>
#include <queue>

class Player {
public:
	Player(int index, int robots_num, Field *field) : index_(index), robots_num_(robots_num), field_(field) {
		CreateRobots();
		robots_alive = robots_num;
        
	}

    void PrintRobotsStatus();

	bool CreateRobots();

    bool CreateQ();

	bool MakeMove();

    bool SkipMove();

    bool CheckIfLose();

    bool PlayerWins();

    int GetCurPoints();

    bool ChargeRobots();
protected:
	int index_;
    int points = 0;
    bool lose = false;
	std::vector<Robot> robots;
    std::vector<Robot*> robots_queue;
	int robots_alive;
	bool move_status = false;
	int robots_num_;
	Field* field_;
};

