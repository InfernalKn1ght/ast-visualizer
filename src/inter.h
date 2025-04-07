#pragma once

#include "lexer.h"
#include <memory>
#include <QStandardItemModel>

class Node {
public:
    int lexline = 0;
    virtual void print(const std::string &prefix = "", bool has_left = 0) const = 0;
    virtual void append_ast_model_node(QStandardItem *parent) const = 0;
    Node(int _lexline = 0);
    virtual ~Node() = default;
};

class Expr : public Node {
public:
    std::unique_ptr<Token> op; // TODO: change name from op to expr_token
    virtual void print(const std::string &prefix, bool has_left) const override = 0;
    virtual void append_ast_model_node(QStandardItem *parent) const override = 0;
    Expr(std::unique_ptr<Token> _op = nullptr);
    Expr(const Expr &expr);
    virtual ~Expr() = default;
};

class Const : public Expr {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    Const(std::unique_ptr<Token> _const_token = nullptr) : Expr(std::move(_const_token)) {}
    virtual ~Const() = default;
};

class Id : public Expr {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    Id(std::unique_ptr<Token> lexeme = nullptr) : Expr(std::move(lexeme)) {}
    virtual ~Id() = default;
    Id(const Id &id);
};

class Op : public Expr {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override = 0;
    virtual void append_ast_model_node(QStandardItem *parent) const override = 0;
    Op(std::unique_ptr<Token> _op) : Expr(std::move(_op)) {}
    virtual ~Op() = default;
};

class BinaryOp : public Op {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Expr> left_expr, right_expr;
    BinaryOp(std::unique_ptr<Token> _op, std::unique_ptr<Expr> _left_expr, std::unique_ptr<Expr> _right_expr) : Op(std::move(_op)), left_expr(std::move(_left_expr)), right_expr(std::move(_right_expr)) {}
    virtual ~BinaryOp() = default;
};

class UnaryOp : public Op {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Expr> expr;
    UnaryOp(std::unique_ptr<Token> _op, std::unique_ptr<Expr> _expr) : Op(std::move(_op)), expr(std::move(_expr)) {}
    virtual ~UnaryOp() = default;
};

class Stmt : public Node {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override = 0;
    virtual void append_ast_model_node(QStandardItem *parent) const override = 0;
    Stmt() {}
    virtual ~Stmt() {}
};

class Stmts : public Stmt {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Stmt> stmt, next_stmt;
    Stmts(std::unique_ptr<Stmt> _stmt, std::unique_ptr<Stmt> _next_stmt) : stmt(std::move(_stmt)), next_stmt(std::move(_next_stmt)) {}
    virtual ~Stmts() = default;
};

class If : public Stmt {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Stmt> stmt;
    If(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt) : expr(std::move(_expr)), stmt(std::move(_stmt)) {}
    virtual ~If() = default;
};

class IfElse : public If { 
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Stmt> else_stmt;
    IfElse(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _if_stmt, std::unique_ptr<Stmt> _else_stmt) : If(std::move(_expr), std::move(_if_stmt)), else_stmt(std::move(_else_stmt)) {}
    virtual ~IfElse() = default;
};

class While : public Stmt {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Stmt> stmt;
    While(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt) : expr(std::move(_expr)), stmt(std::move(_stmt)) {}
    virtual ~While() = default;
};

class Do : public While { // TODO: change it
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    Do(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt) : While(std::move(_expr), std::move(_stmt)) {}
    virtual ~Do() = default;
};

class Break : public Stmt {
public:
    std::unique_ptr<Stmt> stmt;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    Break(std::unique_ptr<Stmt> _stmt) : stmt(std::move(_stmt)) {}
    virtual ~Break() = default;
};

class Set : public Stmt {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Id> id;
    std::unique_ptr<Expr> expr;
    Set(std::unique_ptr<Id> _id, std::unique_ptr<Expr> _expr) : id(std::move(_id)), expr(std::move(_expr)) {}
};