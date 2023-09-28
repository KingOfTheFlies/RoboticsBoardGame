#include "Field.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool Field::SetWidth(size_t new_width) {
    width = new_width;
    return true;
}

size_t Field::GetWidth() {
    return width;
}

bool Field::SetHeight(size_t new_height) {
    height = new_height;
    return true;
}

size_t Field::GetHeight() {
    return height;
}

bool Field::IncMoves() {
    ++moves_count;
    return true;
}

bool Field::SetStartField(const std::vector<std::vector<std::string>>& new_start_field) {
    start_field.insert(start_field.begin(), new_start_field.begin(), new_start_field.end());
    return true;
}

std::vector<std::vector<std::string>>& Field::GetFieldToChange() {
    return field;
}

std::vector<std::vector<bool>>& Field::GetNetToChange() {
    return net;
}

const std::vector<cell>& Field::GetCellsOfMailBoxes() const {
    return cells_to_get_mail;
}

bool Field::CheckIfSpotIsFree(const cell& c) {
    return field[c.y][c.x] == start_field[c.y][c.x];
}

const cell& Field::GetCellToThrowMail(int num_of_cell) {
    return cells_to_throw_mail[num_of_cell];
}

std::vector<std::vector<bool>>& Field::GetCellsToThrowRobots() {
    return net_to_start;
}
const std::vector<cell>& Field::GetCellToCharge() {
    return cells_to_charge;
}

std::string Field::GetStartCell(int x, int y) {
    return start_field[y][x];
}

bool Field::PrintField() {
    std::cout << "~~~~~~~~~~~~~~~~~~" << '#' << moves_count << "~~~~~~~~~~~~~~~~~~~" << std::endl;
    for (const auto& r : field) {
        for (const std::string& s : r) {
            std::cout << std::setw(4) << s;
        }
        std::cout << std::endl;
    }
    return true;
}

std::pair<TimeSpan, AbstractEvent*> Field::getNearestEvent(std::list<AbstractObject*> objects) {
    return std::move(std::make_pair<TimeSpan, AbstractEvent*>(TimeSpan::max(), nullptr));
}

void Field::update(TimeSpan time_span) {
    return;
}

bool Field::ConfigField() {     
    field.insert(field.begin(), start_field.begin(), start_field.end());
    int col_n = 0;
    int row_n = 0;
    for (const auto& row : start_field) {
        std::vector<bool> temp_row;
        std::vector<bool> temp_row_to_start;
        col_n = 0;
        for (const auto& val : row) {
            if (val[0] != WHITE_CELL && val[0] != GRAY_CELL &&
                val[0] != CELL_TO_GET_MAIL && val[0] != CELL_TO_CHARGE &&
                val[0] != RED_CELL && val[0] != CELL_TO_THROW_MAIL) {
                IpException::ErrorCode errorCode = IpException::ErrorCode::IncorrectInputFile;
                throw IpException(errorCode, "incompatible CSV file");
            }
            if (val[0] == WHITE_CELL || val[0] == GRAY_CELL) {
                temp_row.push_back(true);
                if (val[0] == WHITE_CELL) {
                    temp_row_to_start.push_back(true);
                }
                else {
                    temp_row_to_start.push_back(false);
                }
            } 
            else {
                temp_row.push_back(false);
                temp_row_to_start.push_back(false);
                cell c = { col_n, row_n };
                if (val[0] == CELL_TO_GET_MAIL) {
                    cells_to_get_mail.push_back(std::move(c));
                }
                else if (val[0] == CELL_TO_THROW_MAIL) {
                    std::pair<int, cell> new_pair = std::make_pair<int, cell>(int(val[1] - '0'), std::move(c)); // TODO: двузначные
                    cells_to_throw_mail.insert(std::move(new_pair));
                }
                else if (val[0] == CELL_TO_CHARGE) {
                    cells_to_charge.push_back(std::move(c));
                }
            }
            ++col_n;
        }
        net.push_back(temp_row);
        net_to_start.push_back(temp_row_to_start);
        ++row_n;
    }
    return true;
}

