#include "Field.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

bool Field::PrintField() {
    for (const auto& r : start_field) {
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
    return {TimeSpan::max(), NULL};
}

void Field::update(TimeSpan time_span) {
    return;
}

bool Field::ConfigField() {     //TODO
    return true;
}