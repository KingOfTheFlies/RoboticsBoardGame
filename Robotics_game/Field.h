#pragma once
#include "AbstractModel.h"
#include "IpException.h"

#include <string_view>
#include <vector>
#include <set>

enum CELLS_VALS { CELL_TO_GET_MAIL = 's', CELL_TO_THROW_MAIL = 'y',
                  WHITE_CELL = 'w', GRAY_CELL = 'g', CELL_TO_CHARGE = 'b',
                  RED_CELL = 'r' };

struct cell {
    int x, y;
    bool operator==(const cell& other) const noexcept {
        return x == other.x && y == other.y;
    }

    bool operator!=(const cell& other) const noexcept {
        return x != other.x || y != other.y;
    }

    cell operator+(const cell& other) {
        return { x + other.x, y + other.y };
    }

    cell operator-(const cell& other) {
        return { x - other.x, y - other.y };
    }
    bool operator<(const cell& other) const noexcept {
        // logic here
        return x < other.x || (x == other.x && y < other.y); // for example
    }
};

class Field : public AbstractObject {
public:
    bool IncMoves();

    bool PrintField();

    bool ConfigField();

    bool SetWidth(size_t new_width);

    size_t GetWidth();

    bool SetHeight(size_t new_height);

    size_t GetHeight();

    bool SetStartField(const std::vector<std::vector<std::string>>& new_start_field);

    std::vector<std::vector<std::string>>& GetFieldToChange();

    std::vector<std::vector<bool>>& GetNetToChange();

    const std::vector<cell>& GetCellsOfMailBoxes() const;

    const cell& GetCellToThrowMail(int num_of_cell);

    const std::vector<cell>& GetCellToCharge();

    std::vector<std::vector<bool>>& GetCellsToThrowRobots();

    std::string GetStartCell(int x, int y);

    std::pair<TimeSpan, AbstractEvent*> getNearestEvent(std::list<AbstractObject*> objects) override;
    void update(TimeSpan time_span) override;

    bool CheckIfSpotIsFree(const cell& c);

protected:
    int moves_count = 0;
    std::vector<std::vector<std::string>> start_field;
    size_t width = 0;
    size_t height = 0;
    std::vector<std::vector<std::string>> field;
    std::vector<std::vector<bool>> net;
    std::vector<std::vector<bool>> net_to_start;
    std::vector<cell> cells_to_get_mail;
    std::vector<cell> cells_to_charge;
    std::map<int, cell> cells_to_throw_mail;
};