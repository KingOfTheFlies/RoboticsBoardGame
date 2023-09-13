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

std::string Field::GetStartCell(int x, int y) {
    return start_field[x][y];
}

bool Field::PrintField() {
    for (const auto& r : field) {
        for (const auto& s : r) {
            for (const auto& w : s) {
                std::cout << w;
            }
            std::cout << ' ';
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
    for (const auto& row : start_field) {
        std::vector<bool> temp_row;
        for (const auto& val : row) {
            if (val == "w" || val == "g") {
                temp_row.push_back(true);
            }
            else {
                temp_row.push_back(false);
            }
        }
        net.push_back(temp_row);
    }
    return true;
}

