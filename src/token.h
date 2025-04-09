#pragma once

#include <memory>
#include <string>

/**
 * @brief Enumeration of token tags used in lexical analysis.
 *
 * Contains both single-character tokens and special multi-character tokens.
 */
enum Tag {
    NUM = 256,    ///< Integer number token
    ID,           ///< Identifier token
    REAL,         ///< Real number token
    UNARY_MINUS,  ///< Unary minus operator
    AND,          ///< Logical AND operator
    OR,           ///< Logical OR operator
    GE,           ///< Greater or equal operator
    LE,           ///< Less or equal operator
    EQ,           ///< Equality operator
    FOR,          ///< 'for' keyword
    WHILE,        ///< 'while' keyword
    DO,           ///< 'do' keyword
    IF,           ///< 'if' keyword
    ELSE,         ///< 'else' keyword
    BREAK,        ///< 'break' keyword
    BASIC_TYPE,   ///< Basic type keyword
};

/**
 * @brief Base class for all tokens in lexical analysis.
 */
class Token {
public:
    unsigned int tag_ = 0;  ///< Token type identifier

    /**
     * @brief Prints the token to stdout.
     */
    virtual void print() const;

    /**
     * @brief Returns string representation of the token.
     * @return String representation
     */
    virtual std::string token_string() const;

    /**
     * @brief Creates a copy of the token.
     * @return Unique pointer to the cloned token
     */
    std::unique_ptr<Token> clone() const;

    /**
     * @brief Constructs a Token with optional tag.
     * @param tag Token type identifier (default 0)
     */
    Token(unsigned int tag = 0);

    virtual ~Token() {}

protected:
    /**
     * @brief Virtual method for implementing clone functionality.
     * @return Pointer to new Token instance
     */
    virtual Token *get_clone() const;
};

/**
 * @brief Token class for words (identifiers and keywords).
 */
class Word : public Token {
public:
    std::string lexeme_ = "";  ///< The actual string value of the word

    void print() const override;
    virtual std::string token_string() const override;

    /**
     * @brief Constructs a Word with optional tag and lexeme.
     * @param tag Token type identifier (default 0)
     * @param lexeme String value (default empty)
     */
    Word(unsigned int tag = 0, std::string lexeme = "");

    virtual ~Word() = default;

protected:
    virtual Word *get_clone() const override;
};

/**
 * @brief Token class for integer numbers.
 */
class Num : public Token {
public:
    int val_ = 0;  ///< Numeric value

    void print() const override;
    virtual std::string token_string() const override;

    /**
     * @brief Constructs a Num with given value.
     * @param val Integer value
     */
    Num(int val);

    virtual ~Num() = default;
};

/**
 * @brief Token class for real numbers.
 */
class Real : public Token {
public:
    double val_ = 0.0;  ///< Numeric value

    void print() const override;
    virtual std::string token_string() const override;

    /**
     * @brief Constructs a Real with given value.
     * @param val Floating-point value
     */
    Real(double val);

    virtual ~Real() = default;
};

/**
 * @brief Token class for type specifications.
 */
class Type : public Word {
public:
    void print() const override;
    virtual std::string token_string() const override;

    /**
     * @brief Constructs a Type with optional lexeme.
     * @param lexeme Type name (default empty)
     */
    Type(std::string lexeme = "");

    /**
     * @brief Copy constructor for Type.
     * @param type Type to copy
     */
    Type(const Type &type);

    virtual ~Type() = default;
};