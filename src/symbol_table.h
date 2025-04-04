#pragma once

#include "inter.h"
#include <string>
#include <unordered_map>

class STable {
private:
    std::shared_ptr<STable> prev; 
    std::unordered_map<std::string, Id> table;

public:
    std::unique_ptr<Id> get(std::string &lexeme);
    void put(std::string lexeme, Id id);
    STable(std::shared_ptr<STable> _prev = nullptr);
    ~STable() {}
};

