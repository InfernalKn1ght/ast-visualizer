#include "token.h"

#include <iostream>

Token::Token(unsigned int tag) : tag_(tag) {}

void Token::print() const { std::cout << (char)tag_; }

unsigned int Token::get_tag() const { return tag_; }

void Token::set_tag(unsigned int tag) { tag_ = tag; }

std::unique_ptr<Token> Token::clone() const {
    return std::unique_ptr<Token>(get_clone());
}

Token *Token::get_clone() const { return new Token(*this); }

Word::Word(unsigned int tag, std::string lexeme)
    : Token(tag), lexeme_(lexeme) {}

Word *Word::get_clone() const { return new Word(*this); }

void Word::print() const {
    std::cout << "[tag: " << get_tag() << "] " << lexeme_;
}

std::string Word::get_lexeme() const { return lexeme_; }

void Word::set_lexeme(std::string &lexeme) { lexeme_ = lexeme; }

Num::Num(int val) : Token(Tag::NUM), val_(val) {}

int Num::get_val() const { return val_; }

void Num::set_val(int val) { val_ = val; }

void Num::print() const { std::cout << "[tag: " << get_tag() << "] " << val_; }

Real::Real(double val) : Token(Tag::REAL), val_(val) {}

void Real::print() const { std::cout << "[tag: " << get_tag() << "] " << val_; }

double Real::get_val() const { return val_; }

void Real::set_val(double val) { val_ = val; }

Type::Type(const Type &type) {}

void Type::print() const {
    std::cout << "[tag: " << get_tag() << "] " << get_lexeme();
}

std::string Token::token_string() const {
    const char c = (char)tag_;
    return std::string{c};
}

std::string Word::token_string() const { return lexeme_; }

std::string Num::token_string() const { return std::to_string(val_); }

std::string Real::token_string() const { return std::to_string(val_); }

std::string Type::token_string() const { return get_lexeme(); }

Type::Type(std::string lexeme) : Word(Tag::BASIC_TYPE, lexeme) {}