#pragma once

#include <memory>
#include <string>

enum Tag {
    NUM = 256,
    ID,
    REAL,
    UNARY_MINUS,
    AND,
    OR,
    GE,
    LE,
    EQ,
    FOR,
    WHILE,
    DO,
    IF,
    ELSE,
    BREAK,
    BASIC_TYPE,
};

class Token {
public:
    unsigned int tag;
    virtual void print() const;
    std::unique_ptr<Token> clone() const;

    Token(unsigned int _tag = 0) : tag(_tag) {}
    // Token(const Token &token);
    virtual ~Token() {}

protected:
    virtual Token *get_clone() const;
};

class Word : public Token {
public:
    std::string lexeme;
    void print() const override;

    Word(unsigned int _tag = 0, std::string _lexeme = "") : Token(_tag), lexeme(_lexeme) {}
    // Word(const Word &word);
    virtual ~Word() = default;

protected:
    virtual Word *get_clone() const override;
};

class Num : public Token {
public:
    int val;
    void print() const override;
    Num(int _val) : Token(Tag::NUM), val(_val) {}
    virtual ~Num() = default;
};

class Real : public Token {
public:
    double val;
    void print() const override;
    Real(double _val) : Token(Tag::REAL), val(_val) {}
    virtual ~Real() = default;
};

class Type : public Word {
public:
    void print() const override;
    Type(std::string _lexeme = "") : Word(Tag::BASIC_TYPE, _lexeme) {}
    Type(const Type &type);
    virtual ~Type() = default;
};