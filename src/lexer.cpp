#include "lexer.h"
#include <iostream>

bool Lexer::lexer_eof() {
    return _reader.reader_eof();
}

void Lexer::read_peek() {
    _reader.read_symbol(_peek);
}

bool Lexer::next_char(const char &c) {
    read_peek();
    if (c != _peek) {
        return 0;
    }
    _peek = ' ';
    return 1;
}

void Lexer::skip_whitespace() {
    while (!lexer_eof()) {
        if (_peek != ' ' && _peek != '\t' && _peek != '\n') {
            break;
        }
        if (_peek == '\n') {
            ++line;
        }
        read_peek();
    }
}

void Lexer::acc_number(std::string &acc) {
    do {
        acc.push_back(_peek);
        read_peek();
    } while (!lexer_eof() && std::isdigit(_peek));
}

void Lexer::acc_word(std::string &acc) {
    do {
        acc.push_back(_peek);
        read_peek();
    } while (!lexer_eof() && is_alpha_or_digit(_peek));
}

bool Lexer::is_alpha_or_digit(char &c) {
    return std::isdigit(c) || std::isalpha(c);
}

std::unique_ptr<Token> Lexer::make_const_token() {
    std::string acc;
    acc_number(acc);
    if (_peek == '.') {
        acc_number(acc);
        return std::make_unique<Real>(std::stod(acc));
    }
    return std::make_unique<Num>(std::stoi(acc));
}

std::unique_ptr<Token> Lexer::make_word_token() {
    std::string acc;
    acc_word(acc);
    if (_word_table.contains(acc)) {
        return std::make_unique<Word>(_word_table[acc]);
    }
    return std::make_unique<Word>(Tag::ID, acc);
}

std::unique_ptr<Token> Lexer::make_char_token() {
    char chtag = _peek;
    _peek = ' ';
    return std::make_unique<Token>(chtag);
}

std::unique_ptr<Token> Lexer::make_token() {
    if (std::isdigit(_peek)) {
        return make_const_token();
    } else if (std::isalpha(_peek)) {
        return make_word_token();
    } else {
        return make_char_token();
    }
}

std::unique_ptr<Token> Lexer::scan() {
    skip_whitespace();

    switch (_peek) {
    case '&':
        if (next_char('&')) {
            return std::make_unique<Word>(_word_table["&&"]);
        }
        return std::make_unique<Token>('&');
    case '|':
        if (next_char('|')) {
            return std::make_unique<Word>(_word_table["||"]);
        }
        return std::make_unique<Token>('|');
    case '<':
        if (next_char('=')) {
            return std::make_unique<Word>(_word_table["<="]);
        }
        return std::make_unique<Token>('<');
    case '>':
        if (next_char('=')) {
            return std::make_unique<Word>(_word_table[">="]);
        }
        return std::make_unique<Token>('>');
    case '=':
        if (next_char('=')) {
            return std::make_unique<Word>(_word_table["=="]);
        }
        return std::make_unique<Token>('=');

    default:
        return make_token();
    }
}

void Lexer::reserve(Word word) {
    _word_table.emplace(word.lexeme, word);
}

Lexer::Lexer(const std::string &file_name) : _reader(file_name) {
    reserve(Word(Tag::AND, "&&"));
    reserve(Word(Tag::OR, "||"));
    reserve(Word(Tag::LE, "<="));
    reserve(Word(Tag::GE, ">="));
    reserve(Word(Tag::EQ, "=="));
    reserve(Word(Tag::FOR, "for"));
    reserve(Word(Tag::WHILE, "while"));
    reserve(Word(Tag::DO, "do"));
    reserve(Word(Tag::IF, "if"));
    reserve(Word(Tag::ELSE, "else"));
    reserve(Word(Tag::BREAK, "break"));
    reserve(Type("int"));
    reserve(Type("float"));
    reserve(Type("char"));
}