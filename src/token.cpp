#include "token.h"
#include <iostream>

//Token::Token(const Token &token) : tag(token.tag) {}

void Token::print() const {
    std::cout << (char)tag;
}

std::unique_ptr<Token> Token::clone() const {
    return std::unique_ptr<Token>(get_clone());
}

Token *Token::get_clone() const {
    return new Token(*this);
}

//Word::Word(const Word &word) : lexeme(word.lexeme) {}

Word *Word::get_clone() const {
    return new Word(*this);
}

void Word::print() const {
    std::cout << "[tag: " << tag << "] " <<lexeme;
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
