#pragma once

#include <fstream>

class Reader {
private:
    std::ifstream input_text;

public:
    bool read_symbol(char &peek);
    Reader(const std::string &file_name);
    ~Reader();
};