#include "Field.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Field::Field(std::string_view input_file) {
    ConfigField(input_file);
}

bool Field::ConfigField(std::string_view input_file) {
    std::ifstream file;
    std::string name(input_file);
    file.open(name, std::ios_base::in);
    /*if (!file.is_open() || file.bad()) {
        IpException::ErrorCode errorCode = IpException::ErrorCode::IncorrectBMP;
        throw IpException(errorCode, "invalid BMP file");
    }*/ 
    std::vector<std::string> row;
    std::string line, word, temp;
    
    while(file >> temp) {
        row.clear();
        std::getline(file, line);

        std::stringstream s(line);
        
        while (std::getline(s, word, ',')) { //TODO: exception if not chars
            row.push_back(word);
        }
        start_field.push_back(row);
    }
    return true;
}