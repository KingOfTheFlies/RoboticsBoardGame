#pragma once

#include "Field.h"
#include "Dice.h"

#include <string>

enum CONSTS { MAX_BATTERY_VALUE = 70, BATTERY_PER_MOVE = 2, INFTY = 10000000, BATTERY_PER_CHARGE = 16 };

class Robot {
public:
	Robot(int player_index, int index, Field* field) : player_index_(player_index), index_(index), field_(field) {
        visited = std::vector<std::vector<int>>(field_->GetHeight(), std::vector<int>(field_->GetWidth(), -1));
    }

    int GetIndex();

    std::string GetStatus();

    const cell& GetCurPos();

    int GetNumOfDelivering();

    bool ChangeStatus(std::string new_status);

    bool ThrowField(const cell& to);

    bool IsOnChargeSpot();

    const std::vector<cell>& GetPath();

    bool IsAlive();

    bool IncBattery();

    int GetBattery();

    int MakeMove();

    bool OnField();

    bool IsPointGranted();

    bool IsBlocked();

    bool CalculatePath();
protected:
    bool MakeStep();
    bool NeedToChangePath();
    int CheckPathFromDestToCharge();
    bool FindDestForFree(const std::vector<cell>& directions, int& path_len);
    bool FindDestForDelivering(const std::vector<cell>& directions, int& path_len);

    void bfs(cell from);

protected:
    Dice dice;
	int index_;
	int battery = MAX_BATTERY_VALUE;
    int player_index_;
	std::string status = "free"; // free/blocked/delivering/charging/need_to_charge
	bool alive = true;
	bool on_field = false;
    bool on_charge_spot = false;
    bool path_calculated = false;
    bool point_granted = false;
    int num_of_deliver_cell = 0;            
	std::string pos = "00";     // TODO
    cell cur_pos = {-1, -1};
    cell min_move = {-1, -1};
    cell cur_destination = { -1, -1 };
    cell premove_to_dest = { -1, -1 };
	Field* field_;
    std::vector<std::vector<int>> visited;
    std::vector<cell> path;
    std::map<cell, cell> parrent_cells;
public:
    bool move_missed = false;
};

