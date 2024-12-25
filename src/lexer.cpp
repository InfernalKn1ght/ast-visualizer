#include "lexer.h"
#include <iostream>
// TODO: все таки переписать с unique_ptr
void Lexer::reserve(Word word) {
    word_table.emplace(word.lexeme, word);
}

bool Lexer::read_char() {
    return reader.read_symbol(peek);
}

bool Lexer::next_char(const char &c) {
    if (!read_char() || c != peek) {
        return 0;
    }
    peek = ' ';
    return 1;
}

void Lexer::skip_whitespace() {
    do {
        if (peek == '\n') {
            ++line;
            continue;
        }
        if (peek != ' ' && peek != '\t') {
            break;
        }
    } while (read_char());
}

void Lexer::acc_number(std::string &acc) {
    do {
        acc.push_back(peek);
    } while (read_char() && std::isdigit(peek));
}

bool Lexer::is_alpha_or_digit(char &c) {
    return std::isdigit(c) || std::isalpha(c);
}

std::unique_ptr<Token> Lexer::scan() {
    skip_whitespace();

    switch (peek) {
    case '&':
        if (next_char('&')) {
            return std::make_unique<Word>(word_table["&&"]);
        }
        return std::make_unique<Token>('&');
    case '|':
        if (next_char('|')) {
            return std::make_unique<Word>(word_table["||"]);
        }
        return std::make_unique<Token>('|');
    case '<':
        if (next_char('=')) {
            return std::make_unique<Word>(word_table["<="]);
        }
        return std::make_unique<Token>('<');
    case '>':
        if (next_char('=')) {
            return std::make_unique<Word>(word_table[">="]);
        }
        return std::make_unique<Token>('>');
    case '=':
        if (next_char('=')) {
            return std::make_unique<Word>(word_table["=="]);
        }
        return std::make_unique<Token>('=');

    default:
        break;
    }

    std::string acc;
    if (std::isdigit(peek)) {
        acc_number(acc);
        if (peek == '.') {
            acc.push_back('.');
            if (read_char()) { // TODO: Error
                acc_number(acc);
                return std::make_unique<Real>(std::stod(acc));
            }
        }
        return std::make_unique<Num>(std::stoi(acc));
    }
    if (std::isalpha(peek)) {
        do {
            acc.push_back(peek);
        } while (read_char() && is_alpha_or_digit(peek));

        if (word_table.contains(acc)) {
            return std::make_unique<Word>(word_table[acc]);
        }
        return std::make_unique<Word>(Tag::ID, acc);
    }
    char chtag = peek;
    peek = ' ';
    return std::make_unique<Token>(chtag);
}

Lexer::Lexer(const std::string &file_name) : reader(file_name) { // Здесь резервируются ключевые слова в хэш-таблице
    reserve(Word(Tag::AND, "&&"));                               // TODO: позже добавить все оставшиеся ключевые слова
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