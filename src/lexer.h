#pragma once

#include "reader.h"
#include "token.h"
#include <memory>
#include <unordered_map>

class Lexer {
private:
    Reader reader;
    char peek = ' ';
    std::unordered_map<std::string, Word> word_table;
    void reserve(Word word);
    void skip_whitespace();
    bool read_char();
    bool next_char(const char &c);
    void acc_number(std::string &acc);
    bool is_alpha_or_digit(char &c);

public:
    unsigned int line = 0;

    std::unique_ptr<Token> scan();
    Lexer(const std::string &file_name);
};