#include "Robot.h"

#include <queue>
#include <iostream>

bool Robot::ThrowField(const cell& to) {
    cur_pos = {to.x, to.y};
    on_field = true;
    field_->GetCellsToThrowRobots()[to.y][to.x] = false;
    field_->GetNetToChange()[to.y][to.x] = false;
    field_->GetFieldToChange()[cur_pos.y][cur_pos.x] = std::to_string(player_index_) + '-' + std::to_string(index_);
    return true;
}

int Robot::GetIndex() {
    return index_;
}

bool Robot::IncBattery() {
    battery += BATTERY_PER_CHARGE;
    return true;
}

int Robot::GetBattery() {
    return battery;
}

bool Robot::IsBlocked() {
    return status == "blocked";
}
const cell& Robot::GetCurPos() {
    return cur_pos;
}

int Robot::GetNumOfDelivering() {
    return num_of_deliver_cell;
}

std::string Robot::GetStatus() {
    return status;
}

bool Robot::IsOnChargeSpot() {
    return on_charge_spot;
}

bool Robot::ChangeStatus(std::string new_status) {
    status = new_status;
    return true;
}

bool Robot::IsPointGranted() {
    return point_granted;
}

bool Robot::IsAlive() {
    return alive;
}

bool Robot::OnField() {
    return on_field;
}

bool Robot::FindDestForFree(const std::vector<cell>& directions, int& path_len) {
    const std::vector<cell>& mail_boxes = field_->GetCellsOfMailBoxes();
    for (const cell& mail_cell : mail_boxes) {
        for (const cell& delta : directions) {
            int _x = mail_cell.x + delta.x, _y = mail_cell.y + delta.y;
            if (_x >= 0 && _y >= 0 && _x < field_->GetWidth() && _y < field_->GetHeight() &&
                field_->GetNetToChange()[_y][_x] && visited[_y][_x] != -1) {
                if (visited[_y][_x] + 1 < path_len) {
                    path_len = visited[_y][_x] + 1;
                    premove_to_dest = { delta.x, delta.y };
                    cur_destination = { mail_cell.x, mail_cell.y };
                }
            }
        }
    }
    return true;
}

bool Robot::FindDestForDelivering(const std::vector<cell>& directions, int& path_len) {
    const cell& cell_to_throw_mail = field_->GetCellToThrowMail(num_of_deliver_cell);
    for (const cell& delta : directions) {
        int _x = cell_to_throw_mail.x + delta.x, _y = cell_to_throw_mail.y + delta.y;
        if (_x >= 0 && _y >= 0 && _x < field_->GetWidth() && _y < field_->GetHeight() &&
            field_->GetNetToChange()[_y][_x] && visited[_y][_x] != -1) {
            if (visited[_y][_x] + 1 < path_len) {
                path_len = visited[_y][_x] + 1;
                premove_to_dest = { delta.x,  delta.y };
                cur_destination = { cell_to_throw_mail.x, cell_to_throw_mail.y };
            }
        }
    }
    return true;
}

bool Robot::CalculatePath() {
    if (status == "charging") {
        if (num_of_deliver_cell != 0) {
            ChangeStatus("delivering");
        }
        else {
            ChangeStatus("free");
        }
    }
    int path_len = INFTY;
    int path_len_to_charge = INFTY;
    path.clear();
    std::vector<cell> directions = { {-1, 0}, { +1, 0 }, { 0, -1 }, { 0, +1 } };
    bool blocked = true;
    for (cell& delta : directions) {
        if (cur_pos == cur_destination && !on_charge_spot) {
            break;
        }
        cell neighbour_cell = delta + cur_pos;
        if (neighbour_cell.x >= 0 && neighbour_cell.y >= 0 && 
            neighbour_cell.x < field_->GetWidth() && neighbour_cell.y < field_->GetHeight() &&
            (field_->GetNetToChange()[neighbour_cell.y][neighbour_cell.x] || 
                field_->GetFieldToChange()[neighbour_cell.y][neighbour_cell.x][0] == CELL_TO_CHARGE)) {
            min_move.x = delta.x;
            min_move.y = delta.y;
            blocked = false;       
        }
        if (neighbour_cell == cur_destination && field_->CheckIfSpotIsFree(cur_destination)) {
            path.push_back(cur_pos);
            path.push_back(cur_destination);
            return true;
        }
    }

    if (blocked) {
        ChangeStatus("blocked");
        path_calculated = true;
        return false;
    }
    else if (status == "blocked") {
        if (num_of_deliver_cell == 0) {
            ChangeStatus("free");
        }
        else if (on_charge_spot) {
            ChangeStatus("charging");
        }
        else {
            ChangeStatus("delivering");
        }
    } 
    bfs(cur_pos);
    if (status == "free") {
        FindDestForFree(directions, path_len);
        if ((cur_destination.x == -1 && cur_destination.y == -1) || path_len == INFTY) {
            path.push_back(cur_pos);
            path.push_back(cur_pos + min_move);
            return false;
        }
    }
    else if (status == "delivering") {
        FindDestForDelivering(directions, path_len);
        if ((cur_destination.x == -1 && cur_destination.y == -1) || path_len == INFTY) {
            path.push_back(cur_pos);
            path.push_back(cur_pos + min_move);
            return false;
        }
    }
    if (status == "delivering" || status == "free") {
        path_len_to_charge = CheckPathFromDestToCharge();
        if (path_len_to_charge != INFTY && battery < (path_len_to_charge + path_len) * BATTERY_PER_MOVE) {
            if (on_charge_spot) {
                ChangeStatus("charging");
                return false;
            }
            ChangeStatus("need_to_charge");
        }
    }
    if (status == "need_to_charge") {
        const std::vector<cell>& cells_to_charge = field_->GetCellToCharge();
        for (const cell& charge_cell : cells_to_charge) {
            for (const cell& delta : directions) {
                int _x = charge_cell.x + delta.x, _y = charge_cell.y + delta.y;
                if (_x >= 0 && _y >= 0 && _x < field_->GetWidth() && _y < field_->GetHeight() &&
                    field_->GetNetToChange()[_y][_x] && visited[_y][_x] != -1) {
                    if (visited[_y][_x] + 1 < path_len) {
                        path_len = visited[_y][_x] + 1;
                        premove_to_dest = { delta.x,  delta.y };
                        cur_destination = { charge_cell.x, charge_cell.y };
                    }
                }
            }
        }
    }

    cell v = (cur_destination + premove_to_dest);
    while (v != cur_pos) {
        path.push_back(v);
        v = parrent_cells[v];
    }
    path.push_back(cur_pos);
    std::reverse(path.begin(), path.end());
    path.push_back(cur_destination);
    path_calculated = true;
    return true;
}

int Robot::CheckPathFromDestToCharge() {
    const std::vector<cell>& cells_to_charge = field_->GetCellToCharge();
    std::vector<std::vector<bool>> net_to_charge = field_->GetNetToChange();
    std::vector<std::vector<int>> charge_visited = std::vector<std::vector<int>>(field_->GetHeight(), std::vector<int>(field_->GetWidth(), -1));
    for (const cell& charge_cell : cells_to_charge) {
        net_to_charge[charge_cell.y][charge_cell.x] = true;
    }
    net_to_charge[cur_pos.y][cur_pos.x] = true;
    std::queue<cell> q;
    q.push(cur_destination);
    std::vector<cell> directions = { {-1, 0}, { +1, 0 }, { 0, -1 }, { 0, +1 } };
    charge_visited[cur_destination.y][cur_destination.x] = 0;
    while (!q.empty()) {
        cell c = q.front();
        q.pop();
        for (const cell& delta : directions) {
            int _x = c.x + delta.x, _y = c.y + delta.y;
            if (_x >= 0 && _y >= 0 && _x < field_->GetWidth() && _y < field_->GetHeight() &&
                net_to_charge[_y][_x] && charge_visited[_y][_x] == -1) {
                charge_visited[_y][_x] = charge_visited[c.y][c.x] + 1;
                q.push({ _x, _y });
            }
        }
    }
    int min_path_to_charge = INFTY;
    for (const cell& charge_cell : cells_to_charge) {
        if (charge_visited[charge_cell.y][charge_cell.x] < min_path_to_charge) {
            min_path_to_charge = charge_visited[charge_cell.y][charge_cell.x];
        }
    }
    return min_path_to_charge;
}

void Robot::bfs(cell from) {
    std::queue<cell> q;
    q.push(from);
    std::vector<cell> directions = { {-1, 0}, { +1, 0 }, { 0, -1 }, { 0, +1 } };
    visited = std::vector<std::vector<int>>(field_->GetHeight(), std::vector<int>(field_->GetWidth(), -1));
    visited[from.y][from.x] = 0;
    while (!q.empty()) {
        cell c = q.front();
        q.pop();
        for (const cell& delta : directions) {
            int _x = c.x + delta.x, _y = c.y + delta.y;
            if (_x >= 0 && _y >= 0 && _x < field_->GetWidth() && _y < field_->GetHeight() &&
                field_->GetNetToChange()[_y][_x] && visited[_y][_x] == -1) {
                visited[_y][_x] = visited[c.y][c.x] + 1;
                q.push({ _x, _y });
                parrent_cells[{_x, _y}] = { c.x, c.y };
            }
        }
    }
}

bool Robot::NeedToChangePath() {
    if (status == "blocked") {
        return true;
    }
    if (path_calculated) {
        for (const cell& c : path) {
            if (!field_->GetNetToChange()[c.y][c.x]) {
                return true;
            }
        }
        return false;
    }
    return true;
}

bool Robot::MakeStep() {            // if got point
    move_missed = false;
    bool return_val = false;
    path.erase(path.begin());

    field_->GetCellsToThrowRobots()[cur_pos.y][cur_pos.x] = true;
    field_->GetFieldToChange()[cur_pos.y][cur_pos.x] = field_->GetStartCell(cur_pos.x, cur_pos.y);
    if (field_->GetStartCell(cur_pos.x, cur_pos.y)[0] == GRAY_CELL || 
        field_->GetStartCell(cur_pos.x, cur_pos.y)[0] == WHITE_CELL) {
        field_->GetNetToChange()[cur_pos.y][cur_pos.x] = true;
    }
    else {
        field_->GetNetToChange()[cur_pos.y][cur_pos.x] = false;
    }
    if (path[0] == cur_destination) {
        if (status == "free") {
            ChangeStatus("delivering");         // need to change robots queue
            num_of_deliver_cell = dice.ThrowDice();
        }
        else if (status == "delivering") {
            ChangeStatus("free");               // need to change robots queue
            num_of_deliver_cell = 0;
            return_val = true;
            // TODO: get point
        }   
        else if (status == "need_to_charge") {
            ChangeStatus("charging");
            on_charge_spot = true;
        }
    }
    cur_pos = path[0];
    field_->GetNetToChange()[cur_pos.y][cur_pos.x] = false;
    field_->GetFieldToChange()[cur_pos.y][cur_pos.x] = std::to_string(player_index_) + '-' + std::to_string(index_);
    field_->GetCellsToThrowRobots()[cur_pos.y][cur_pos.x] = false;
    if (field_->GetStartCell(cur_pos.x, cur_pos.y)[0] != CELL_TO_CHARGE) {
        on_charge_spot = false;
    }
    battery -= BATTERY_PER_MOVE;
    return return_val;
}

int Robot::MakeMove() {        // true: made move, false: not {-2 - stepped on spot, -1 - change_priority/blocked/died, 0 - moved, 1 - got_point}
    bool destination_found = false;
    if (NeedToChangePath()) {
        destination_found = CalculatePath();
    }
    if (status == "blocked") {
        return -1;
    }
    if (!move_missed && ((path.size() == 2 && path[1] == cur_destination && !field_->CheckIfSpotIsFree(cur_destination)) ||
        (!destination_found && ((field_->GetStartCell(cur_pos.x, cur_pos.y)[0] != CELL_TO_THROW_MAIL &&
            field_->GetStartCell(cur_pos.x, cur_pos.y)[0] != CELL_TO_GET_MAIL) || on_charge_spot)))) {
        return -1; //change priority
    }
    if (move_missed && (!destination_found || !field_->CheckIfSpotIsFree(cur_destination) )) {
        path.clear();
        path.push_back(cur_pos);
        path.push_back(cur_pos + min_move);
    }

    point_granted = MakeStep();
    if (battery <= 0 && !on_charge_spot) {
        ChangeStatus("dead");
        alive = false;
        return 0;
    }
    if (cur_pos == cur_destination && (field_->GetStartCell(cur_pos.x, cur_pos.y)[0] == CELL_TO_THROW_MAIL ||
        field_->GetStartCell(cur_pos.x, cur_pos.y)[0] == CELL_TO_GET_MAIL)) {
        cur_destination = { -1, -1 };
        return -2;  // step on the next move too
    }
    return 0;
}

const std::vector<cell>& Robot::GetPath() {
    if (NeedToChangePath()) {
        CalculatePath();
    }
    return path;
}