#pragma once

#include "lexer.h"
#include <memory>

class Node {
public:
    int lexline = 0;
    Node(int _lexline = 0);
    virtual ~Node() = default;
};

class Expr : public Node {
public:
    std::unique_ptr<Token> op;
    Expr(std::unique_ptr<Token> _op = nullptr);
    Expr(const Expr &expr);
    virtual ~Expr() = default;
};

class Const : public Expr {
public:
    Const(std::unique_ptr<Token> _op = nullptr) : Expr(std::move(_op)) {}
    virtual ~Const() = default;
};

class Id : public Expr {
public:
    Id(std::unique_ptr<Token> lexeme = nullptr) : Expr(std::move(lexeme)) {}
    virtual ~Id() = default;
    Id(const Id &id);
};

class Op : public Expr {
public:
    Op(std::unique_ptr<Token> _op) : Expr(std::move(_op)) {}
    virtual ~Op() = default;
};

class BinaryOp : public Op {
public:
    std::unique_ptr<Expr> left_expr, right_expr;
    BinaryOp(std::unique_ptr<Token> _op, std::unique_ptr<Expr> _left_expr, std::unique_ptr<Expr> _right_expr) : Op(std::move(_op)), left_expr(std::move(_left_expr)), right_expr(std::move(_right_expr)) {}
    virtual ~BinaryOp() = default;
};

class UnaryOp : public Op {
public:
    std::unique_ptr<Expr> expr;
    UnaryOp(std::unique_ptr<Token> _op, std::unique_ptr<Expr> _expr) : Op(std::move(_op)), expr(std::move(_expr)) {}
    virtual ~UnaryOp() = default;
};

class Stmt : public Node {
public:
    Stmt() {}
    virtual ~Stmt() {}
};

class Stmts : public Stmt {
public:
    std::unique_ptr<Stmt> stmt, next_stmt;
    Stmts(std::unique_ptr<Stmt> _stmt, std::unique_ptr<Stmt> _next_stmt) : stmt(std::move(_stmt)), next_stmt(std::move(_next_stmt)) {}
    virtual ~Stmts() = default;
};

class If : public Stmt {
public:
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Stmt> stmt;
    If(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt) : expr(std::move(_expr)), stmt(std::move(_stmt)) {}
    virtual ~If() = default;
};

class IfElse : public If {
public:
    std::unique_ptr<Stmt> else_stmt;
    IfElse(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _if_stmt, std::unique_ptr<Stmt> _else_stmt) : If(std::move(_expr), std::move(_if_stmt)), else_stmt(std::move(_else_stmt)) {}
    virtual ~IfElse() = default;
};

class While : public Stmt {
public:
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Stmt> stmt;
    While(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt) : expr(std::move(_expr)), stmt(std::move(_stmt)) {}
    virtual ~While() = default;
};

class Do : public While {
public:
    Do(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt) : While(std::move(_expr), std::move(_stmt)) {}
    virtual ~Do() = default;
};

class Break : public Stmt {
public:
    std::unique_ptr<Stmt> stmt;
    Break(std::unique_ptr<Stmt> _stmt) : stmt(std::move(_stmt)) {}
    virtual ~Break() = default;
};

class Set : public Stmt {
public:
    std::unique_ptr<Id> id;
    std::unique_ptr<Expr> expr;
    Set(std::unique_ptr<Id> _id, std::unique_ptr<Expr> _expr) : id(std::move(_id)), expr(std::move(_expr)) {}
};