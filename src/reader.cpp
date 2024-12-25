#include "reader.h"
#include <iostream>

Reader::Reader(const std::string &file_name) {
    input_text.open(file_name);
    if (!input_text.is_open()) { // TODO: переписать с throw exception
        std::cout << "Failed to open " << '"' << file_name << '"' << std::endl;
    }
}

Reader::~Reader() {
    if (input_text.is_open()) {
        input_text.close();
    }
}

bool Reader::read_symbol(char &peek) {
    if (input_text.get(peek)) {
        return 1;
    } else {
        return 0;
    }
}