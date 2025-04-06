#include "parser.h"
#include <iostream>

Parser::Parser(const std::string &file_name) : lex(file_name) {
    top_table = std::make_shared<STable>();
    next();
}

void Parser::next() {
    next_token = lex.scan();
}

void Parser::match(unsigned int tok) {
    if (tok == next_token->tag) {
        std::cout << "token is correct" << std::endl;
        return;
    }
    std::cout << "token is not correct" << std::endl;
}

void Parser::match_and_move(unsigned int tok) {
    match(tok);
    next();
}

std::unique_ptr<Stmt> Parser::program() { // TODO: add decls check before first block (global variables)
    std::unique_ptr<Stmt> stmt = block();
    return stmt;
}

std::unique_ptr<Stmt> Parser::block() {
    match_and_move('{');
    std::shared_ptr<STable> saved_table = top_table;
    top_table = std::make_shared<STable>(saved_table);
    decls();
    std::unique_ptr<Stmt> st = stmts();
    match_and_move('}');
    top_table = saved_table;
    return st;
}

void Parser::decls() {
    while (next_token->tag == Tag::BASIC_TYPE) {
        auto p = type();
        match(Tag::ID);
        std::string id_lexeme = static_cast<Word *>(next_token.get())->lexeme;
        Id id(std::move(next_token));
        next();
        match_and_move(';');
        top_table->put(id_lexeme, id);
    }
}

std::unique_ptr<Type> Parser::type() {
    match_and_move(Tag::BASIC_TYPE);
    std::string lexeme = static_cast<Type *>(next_token.get())->lexeme;
    return std::make_unique<Type>(lexeme);
}

std::unique_ptr<Stmt> Parser::stmts() {
    if (next_token->tag == '}') {
        return nullptr;
    }
    std::unique_ptr<Stmt> stmt1 = stmt();
    std::unique_ptr<Stmt> stmt2 = stmts();
    return std::make_unique<Stmts>(std::move(stmt1), std::move(stmt2));
}

std::unique_ptr<Stmt> Parser::stmt() {
    std::unique_ptr<Expr> stmt_expr;
    std::unique_ptr<Stmt> stmt1, stmt2;
    switch (next_token->tag) {
    case ';':
        next();
        return nullptr;
    case Tag::IF:
        match_and_move(Tag::IF);
        match_and_move('(');
        stmt_expr = expr();
        match_and_move(')');
        stmt1 = stmt();
        if (next_token->tag != Tag::ELSE) {
            return std::make_unique<If>(std::move(stmt_expr), std::move(stmt1));
        }
        match_and_move(Tag::ELSE);
        stmt2 = stmt();
        return std::make_unique<IfElse>(std::move(stmt_expr), std::move(stmt1), std::move(stmt2));
    case Tag::WHILE:
        match_and_move(Tag::WHILE);
        match_and_move('(');
        stmt_expr = expr();
        match_and_move(')');
        stmt1 = stmt();
        return std::make_unique<While>(std::move(stmt_expr), std::move(stmt1));
    case Tag::DO:
        match_and_move(Tag::DO);
        stmt1 = stmt();
        match_and_move(Tag::WHILE);
        match_and_move('(');
        stmt_expr = expr();
        match_and_move(')');
        match_and_move(';');
        return std::make_unique<Do>(std::move(stmt_expr), std::move(stmt1));
    case Tag::BREAK:
        match_and_move(Tag::BREAK);
        return std::make_unique<Break>(nullptr);
    case '{':
        return block();
    default:
        return assign();
    }
}

std::unique_ptr<Stmt> Parser::assign() {
    std::unique_ptr<Stmt> set; // TODO: match first, get lexeme after
    std::string id_lexeme = static_cast<Word *>(next_token.get())->lexeme;
    match_and_move(Tag::ID); // TODO: rewrite this mess
    std::unique_ptr<Id> id = top_table->get(id_lexeme);
    if (next_token->tag == '=') { // TODO: add id null ckech
        next(); // TODO: figure out why not match_and_move('=')
        set = std::make_unique<Set>(std::move(id), std::move(expr()));
    }
    match_and_move(';');
    return std::move(set);
    // TODO: add array check
}

std::unique_ptr<Expr> Parser::expr() {
    std::unique_ptr<Expr> exp = term();
    while (next_token->tag == '+' || next_token->tag == '-') {
        std::unique_ptr<Token> tok = std::move(next_token);
        next();
        exp = std::make_unique<BinaryOp>(std::move(tok), std::move(exp), std::move(term()));
    }
    return std::move(exp);
}

std::unique_ptr<Expr> Parser::term() {
    std::unique_ptr<Expr> exp = unary();
    while (next_token->tag == '*' || next_token->tag == '/') {
        std::unique_ptr<Token> tok = std::move(next_token);
        next();
        exp = std::make_unique<BinaryOp>(std::move(tok), std::move(exp), std::move(term()));
    }
    return std::move(exp);
}

std::unique_ptr<Expr> Parser::unary() {
    if (next_token->tag == '-') {
        std::unique_ptr<Token> tok = std::move(next_token);
        next();
        return std::make_unique<UnaryOp>(std::move(tok), std::move(factor()));
    } else {
        return std::move(factor());
    }
}

std::unique_ptr<Expr> Parser::factor() {
    std::unique_ptr<Expr> exp = nullptr;
    std::string lexeme;
    switch (next_token->tag) {
    case '(':
        next();
        exp = expr();
        match_and_move(')');
        return std::move(exp);
    case Tag::NUM:
        exp = std::make_unique<Const>(std::move(next_token));
        next();
        return std::move(exp);
    case Tag::REAL:
        exp = std::make_unique<Const>(std::move(next_token));
        next();
        return std::move(exp);
    case Tag::ID:
        lexeme = static_cast<Word *>(next_token.get())->lexeme;
        next();
        exp = top_table->get(lexeme);
        if (exp == nullptr) {
            // error
        }
        return std::move(exp);
    default:
        // error
        return std::move(exp);
    }
}