#include "token.h"

#include <iostream>

Token::Token(unsigned int tag) : tag_(tag) {}

void Token::print() const { std::cout << (char)tag_; }

std::unique_ptr<Token> Token::clone() const {
    return std::unique_ptr<Token>(get_clone());
}

Token *Token::get_clone() const { return new Token(*this); }

Word::Word(unsigned int tag, std::string lexeme)
    : Token(tag), lexeme_(lexeme) {}

Word *Word::get_clone() const { return new Word(*this); }

void Word::print() const { std::cout << "[tag: " << tag_ << "] " << lexeme_; }

Num::Num(int val) : Token(Tag::NUM), val_(val) {}

void Num::print() const { std::cout << "[tag: " << tag_ << "] " << val_; }

Real::Real(double val) : Token(Tag::REAL), val_(val) {}

void Real::print() const { std::cout << "[tag: " << tag_ << "] " << val_; }

Type::Type(const Type &type) {}

void Type::print() const { std::cout << "[tag: " << tag_ << "] " << lexeme_; }

std::string Token::token_string() const {
    const char c = (char)tag_;
    return std::string{c};
}

std::string Word::token_string() const { return lexeme_; }

std::string Num::token_string() const { return std::to_string(val_); }

std::string Real::token_string() const { return std::to_string(val_); }

std::string Type::token_string() const { return lexeme_; }

Type::Type(std::string lexeme) : Word(Tag::BASIC_TYPE, lexeme) {}