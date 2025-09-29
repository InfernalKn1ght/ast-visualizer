#pragma once

#include <memory>
#include <unordered_map>

#include "reader.h"
#include "token.h"

/**
 * @brief The Lexer class performs lexical analysis of input source code.
 *
 * Converts character streams into tokens by recognizing patterns in the input.
 * Handles whitespace skipping, number/word accumulation, and token creation.
 */
class Lexer {
public:
    unsigned int line_ = 0;  ///< Current line number in source code

    /**
     * @brief Scans the input and returns the next recognized token.
     * @return Unique pointer to the recognized Token
     */
    std::unique_ptr<Token> scan();

    /**
     * @brief Checks if the lexer has reached end of input.
     * @return True if EOF reached, false otherwise
     */
    bool lexer_eof();

    /**
     * @brief Constructs a Lexer for the given input file.
     * @param file_name Path to the source file to analyze
     */
    Lexer(const std::string &file_name);

    Lexer(const Lexer &l);

    ~Lexer() = default;

private:
    Reader reader_;    ///< Input reader for source characters
    char peek_ = ' ';  ///< Lookahead character buffer
    std::unordered_map<std::string, Word>
        word_table_;  ///< Reserved words table

    /**
     * @brief Reads next character into peek buffer.
     */
    void read_peek();

    /**
     * @brief Checks and consumes expected character.
     * @param c Expected character to match
     * @return True if character matched, false otherwise
     */
    bool next_char(const char &c);

    /**
     * @brief Skips whitespace characters and counts newlines.
     */
    void skip_whitespace();

    /**
     * @brief Accumulates digit characters into string.
     * @param acc String accumulator for digits
     */
    void acc_number(std::string &acc);

    /**
     * @brief Accumulates alphanumeric characters into string.
     * @param acc String accumulator for word characters
     */
    void acc_word(std::string &acc);

    /**
     * @brief Checks if character is alphanumeric.
     * @param c Character to check
     * @return True if character is letter or digit
     */
    bool is_alpha_or_digit(char &c);

    /**
     * @brief Creates numeric constant token (int or real).
     * @return Pointer to created Num or Real token
     */
    std::unique_ptr<Token> make_const_token();

    /**
     * @brief Creates word token (identifier or reserved word).
     * @return Pointer to created Word token
     */
    std::unique_ptr<Token> make_word_token();

    /**
     * @brief Creates single-character token.
     * @return Pointer to basic Token
     */
    std::unique_ptr<Token> make_char_token();

    /**
     * @brief Creates appropriate token based on peek character.
     * @return Pointer to created token
     */
    std::unique_ptr<Token> make_token();

    /**
     * @brief Adds reserved word to symbol table.
     * @param word Reserved word to add
     */
    void reserve(Word word);
};