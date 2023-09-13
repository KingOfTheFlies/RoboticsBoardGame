#pragma once

#include "Field.h"

#include <string>

enum CONSTS { MAX_BATTERY_VALUE = 50 };

class Robot {
public:
	Robot(int index, Field* field) : index_(index), field_(field) {}

	bool MakeMove(char dir);

    
protected:
	int index_;
	int battery = MAX_BATTERY_VALUE;
	std::string status = "free"; // free/blocked/delivering
	bool alive = true;
	bool on_filed = false;
	std::string pos = "00";
    cell cur_pos = {-1, -1};
	Field* field_;
};

