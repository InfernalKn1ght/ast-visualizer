#include "lexer.h"

bool Lexer::lexer_eof() { return reader_.reader_eof(); }

void Lexer::read_peek() { reader_.read_symbol(peek_); }

bool Lexer::next_char(const char &c) {
    read_peek();
    if (c != peek_) {
        return 0;
    }
    peek_ = ' ';
    return 1;
}

void Lexer::skip_whitespace() {
    while (!lexer_eof()) {
        if (peek_ != ' ' && peek_ != '\t' && peek_ != '\n') {
            break;
        }
        if (peek_ == '\n') {
            ++line_;
        }
        read_peek();
    }
}

void Lexer::acc_number(std::string &acc) {
    do {
        acc.push_back(peek_);
        read_peek();
    } while (!lexer_eof() && std::isdigit(peek_));
}

void Lexer::acc_word(std::string &acc) {
    do {
        acc.push_back(peek_);
        read_peek();
    } while (!lexer_eof() && is_alpha_or_digit(peek_));
}

bool Lexer::is_alpha_or_digit(char &c) {
    return std::isdigit(c) || std::isalpha(c);
}

std::unique_ptr<Token> Lexer::make_const_token() {
    std::string acc;
    acc_number(acc);
    if (peek_ == '.') {
        acc_number(acc);
        return std::make_unique<Real>(std::stod(acc));
    }
    return std::make_unique<Num>(std::stoi(acc));
}

std::unique_ptr<Token> Lexer::make_word_token() {
    std::string acc;
    acc_word(acc);
    if (word_table_.contains(acc)) {
        return std::make_unique<Word>(word_table_[acc]);
    }
    return std::make_unique<Word>(Tag::ID, acc);
}

std::unique_ptr<Token> Lexer::make_char_token() {
    char chtag = peek_;
    peek_ = ' ';
    return std::make_unique<Token>(chtag);
}

std::unique_ptr<Token> Lexer::make_token() {
    if (std::isdigit(peek_)) {
        return make_const_token();
    } else if (std::isalpha(peek_)) {
        return make_word_token();
    } else {
        return make_char_token();
    }
}

std::unique_ptr<Token> Lexer::scan() {
    skip_whitespace();

    switch (peek_) {
        case '&':
            if (next_char('&')) {
                return std::make_unique<Word>(word_table_["&&"]);
            }
            return std::make_unique<Token>('&');
        case '|':
            if (next_char('|')) {
                return std::make_unique<Word>(word_table_["||"]);
            }
            return std::make_unique<Token>('|');
        case '<':
            if (next_char('=')) {
                return std::make_unique<Word>(word_table_["<="]);
            }
            return std::make_unique<Token>('<');
        case '>':
            if (next_char('=')) {
                return std::make_unique<Word>(word_table_[">="]);
            }
            return std::make_unique<Token>('>');
        case '=':
            if (next_char('=')) {
                return std::make_unique<Word>(word_table_["=="]);
            }
            return std::make_unique<Token>('=');

        default:
            return make_token();
    }
}

void Lexer::reserve(Word word) { word_table_.emplace(word.lexeme_, word); }

Lexer::Lexer(const std::string &file_name) : reader_(file_name) {
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