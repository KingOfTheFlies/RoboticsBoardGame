#pragma once
#include "AbstractModel.h"

#include <string_view>
#include <vector>

struct cell {
    int x, y;
};

class Field : public AbstractObject {
public:
    bool PrintField();

    bool ConfigField();

    bool SetWidth(size_t new_width);

    size_t GetWidth();

    bool SetHeight(size_t new_height);

    size_t GetHeight();

    bool SetStartField(const std::vector<std::vector<std::string>>& new_start_field);

    std::vector<std::vector<std::string>>& GetFieldToChange();

    std::vector<std::vector<bool>>& GetNetToChange();

    std::string GetStartCell(int x, int y);

    std::pair<TimeSpan, AbstractEvent*> getNearestEvent(std::list<AbstractObject*> objects) override;
    void update(TimeSpan time_span) override;

protected:
    int moves_count = 0;
    std::vector<std::vector<std::string>> start_field;
    size_t width = 0;
    size_t height = 0;
    std::vector<std::vector<std::string>> field;
    std::vector<std::vector<bool>> net;
};