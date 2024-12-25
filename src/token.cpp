#include "token.h"
#include <iostream>

//Token::Token(const Token &token) : tag(token.tag) {}

void Token::print() const {
    std::cout << (char)tag << std::endl;
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
    std::cout << tag << " " << lexeme << std::endl;
}

void Num::print() const {
    std::cout << tag << " " << val << std::endl;
}

void Real::print() const {
    std::cout << tag << " " << val << std::endl;
}

Type::Type(const Type &type) {}
