#include "reader.h"

#include <iostream>

Reader::Reader(const std::string &file_name) {
    input_text_.open(file_name);
    if (!input_text_.is_open()) {
        std::cout << "Failed to open " << '"' << file_name << '"' << std::endl;
    }
}

Reader::~Reader() {
    if (input_text_.is_open()) {
        input_text_.close();
    }
}

void Reader::read_symbol(char &peek) { input_text_.get(peek); }

bool Reader::reader_eof() const { return input_text_.eof(); }