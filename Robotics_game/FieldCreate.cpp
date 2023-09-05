#include "FieldCreate.h"

#include <fstream>


FieldCreate::FieldCreate(std::string_view input_file) {
    LoadFromFile(input_file);
}

bool FieldCreate::LoadFromFile(std::string_view input_file) {
    std::ifstream file;
    std::string name(input_file);
    file.open(name, std::ios_base::in);
    /*if (!file.is_open() || file.bad()) {
        IpException::ErrorCode errorCode = IpException::ErrorCode::IncorrectCSV;
        throw IpException(errorCode, "invalid CSV file");
    }*/
    std::vector<std::string> row;
    std::string line, word, temp;

    while (std::getline(file, line)) {
        row.clear();
        std::stringstream s(line);
        while (std::getline(s, word, ',')) { //TODO: exception if not chars
            row.push_back(word);
        }
        field.start_field.push_back(row);
    }
    field.height = field.start_field.size();
    field.width = field.start_field[0].size();
    return true;
}

void FieldCreate::runEvent(std::list<AbstractObject*> objects, TimeSpan time_span) {
    // TODO: logger
    field.lastUpdated = time_span;
    objects.push_back(&field);
}