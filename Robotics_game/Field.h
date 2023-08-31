#pragma once
#include "AbstractModel.cpp"

#include <string_view>
#include <vector>

class Field {
public:
    Field(std::string_view input_file);

    bool ConfigField(std::string_view input_file);

    std::string GetStartCell(int x, int y) {
        return start_field[x][y];
    }

protected:
    int moves_count = 0;
    int time = 0; // TODO
    std::vector<std::vector<std::string>> start_field;
    char** field;
    bool** net;
};