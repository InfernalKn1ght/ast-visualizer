#pragma once

#include "reader.h"
#include "token.h"
#include <memory>
#include <unordered_map>

class Lexer {
public:
    unsigned int line = 0;
    std::unique_ptr<Token> scan();
    bool lexer_eof();
    Lexer(const std::string &file_name);
    ~Lexer() = default;

private:
    Reader _reader;
    char _peek = ' ';
    std::unordered_map<std::string, Word> _word_table;
    void read_peek();
    bool next_char(const char &c);
    void skip_whitespace();
    void acc_number(std::string &acc);
    void acc_word(std::string &acc);
    bool is_alpha_or_digit(char &c);
    std::unique_ptr<Token> make_const_token();
    std::unique_ptr<Token> make_word_token();
    std::unique_ptr<Token> make_char_token();
    std::unique_ptr<Token> make_token();
    void reserve(Word word);
};