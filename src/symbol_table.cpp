#include "symbol_table.h"

STable::STable(std::shared_ptr<STable> _prev) : prev(_prev) {}

std::unique_ptr<Id> STable::get(std::string &lexeme) {
    for (STable *s = this; s != nullptr; s = s->prev.get()) { 
        if (s->table.contains(lexeme)) {
            return std::make_unique<Id>(s->table[lexeme]);
        }
    }
    return nullptr;
}

void STable::put(std::string lexeme, Id id) {
    table.emplace(lexeme, id);
}