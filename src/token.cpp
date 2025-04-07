#include "token.h"
#include <iostream>

void Token::print() const {
    std::cout << (char)tag;
}

std::unique_ptr<Token> Token::clone() const {
    return std::unique_ptr<Token>(get_clone());
}

Token *Token::get_clone() const {
    return new Token(*this);
}

Word *Word::get_clone() const {
    return new Word(*this);
}

void Word::print() const {
    std::cout << "[tag: " << tag << "] " << lexeme;
}

void Num::print() const {
    std::cout << "[tag: " << tag << "] " << val;
}

void Real::print() const {
    std::cout << "[tag: " << tag << "] " << val;
}

Type::Type(const Type &type) {}

void Type::print() const {
    std::cout << "[tag: " << tag << "] " << lexeme;
}

std::string Token::token_string() const {
    char c = (char)tag;
    return std::string{c};
}

std::string Word::token_string() const {
    return lexeme;
}

std::string Num::token_string() const {
    return std::to_string(val);
}

std::string Real::token_string() const {
    return std::to_string(val);
}

std::string Type::token_string() const {
    return lexeme;
}