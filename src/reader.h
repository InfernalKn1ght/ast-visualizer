#pragma once

#include <fstream>

class Reader {
public:
    bool reader_eof() const;
    void read_symbol(char &peek);
    Reader(const std::string &file_name);
    virtual ~Reader();

private:
    std::ifstream _input_text;
};