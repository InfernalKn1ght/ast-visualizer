#include "symbol_table.h"

STable::STable(std::shared_ptr<STable> prev) : prev_(prev) {}

std::unique_ptr<Id> STable::get(std::string &lexeme) {
    for (STable *s = this; s != nullptr; s = s->prev_.get()) {
        if (s->table_.contains(lexeme)) {
            return std::make_unique<Id>(s->table_[lexeme]);
        }
    }
    return nullptr;
}

void STable::put(std::string lexeme, Id id) { table_.emplace(lexeme, id); }