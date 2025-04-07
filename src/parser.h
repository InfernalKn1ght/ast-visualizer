#pragma once

#include "inter.h"
#include "lexer.h"
#include "symbol_table.h"

class Parser {
public:
    Parser(const std::string &file_name);
    std::unique_ptr<Stmt> program();
    std::unique_ptr<Stmt> block();
    void decls();
    std::unique_ptr<Stmt> stmts();
    std::unique_ptr<Type> type();
    std::unique_ptr<Stmt> stmt();
    std::unique_ptr<Expr> expr();
    std::unique_ptr<Stmt> assign();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> factor();

private:
    Lexer lex;
    std::unique_ptr<Token> next_token;
    std::shared_ptr<STable> top_table;
    void next();
    void match(unsigned int tok);
    void match_and_move(unsigned int tok);
};