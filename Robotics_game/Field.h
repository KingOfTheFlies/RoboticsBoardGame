#pragma once
#include "AbstractModel.cpp"

#include <string_view>
#include <vector>

class Field : public AbstractObject {
public:
    Field() {};

    bool PrintField();

    bool ConfigField();

    std::string GetStartCell(int x, int y) {
        return start_field[x][y];
    }

    std::pair<TimeSpan, AbstractEvent*> getNearestEvent(std::list<AbstractObject*> objects) override;
    void update(TimeSpan time_span) override;

    int moves_count = 0;
    std::vector<std::vector<std::string>> start_field;
    size_t width;
    size_t height;
    char** field;
    bool** net;
};