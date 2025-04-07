#include "reader.h"
#include <iostream>

Reader::Reader(const std::string &file_name) {
    _input_text.open(file_name);
    if (!_input_text.is_open()) { 
        std::cout << "Failed to open " << '"' << file_name << '"' << std::endl;
    }
}

Reader::~Reader() {
    if (_input_text.is_open()) {
        _input_text.close();
    }
}

void Reader::read_symbol(char &peek) {
    _input_text.get(peek);
}

bool Reader::reader_eof() const {
    return _input_text.eof();
}