#pragma once

#include "lexer.h"
#include <QStandardItemModel>
#include <memory>

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
    Const(std::unique_ptr<Token> _const_token = nullptr);
    virtual ~Const() = default;
};

class Id : public Expr {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    Id(std::unique_ptr<Token> lexeme = nullptr);
    virtual ~Id() = default;
    Id(const Id &id);
};

class Op : public Expr {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override = 0;
    virtual void append_ast_model_node(QStandardItem *parent) const override = 0;
    Op(std::unique_ptr<Token> _op);
    virtual ~Op() = default;
};

class BinaryOp : public Op {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Expr> left_expr, right_expr;
    BinaryOp(std::unique_ptr<Token> _op, std::unique_ptr<Expr> _left_expr, std::unique_ptr<Expr> _right_expr);
};

class UnaryOp : public Op {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Expr> expr;
    UnaryOp(std::unique_ptr<Token> _op, std::unique_ptr<Expr> _expr);
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
    Stmts(std::unique_ptr<Stmt> _stmt, std::unique_ptr<Stmt> _next_stmt);
    virtual ~Stmts() = default;
};

class If : public Stmt {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Stmt> stmt;
    If(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt);
    virtual ~If() = default;
};

class IfElse : public If {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Stmt> else_stmt;
    IfElse(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _if_stmt, std::unique_ptr<Stmt> _else_stmt);
    virtual ~IfElse() = default;
};

class While : public Stmt {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Stmt> stmt;
    While(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt);
    virtual ~While() = default;
};

class Do : public Stmt {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Expr> expr;
    std::unique_ptr<Stmt> stmt;
    Do(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt);
    virtual ~Do() = default;
};

class Break : public Stmt {
public:
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    Break() {} // TODO: add pointer to enclosing stmt
    virtual ~Break() = default;
};

class Set : public Stmt {
public:
    virtual void print(const std::string &prefix = "", bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    std::unique_ptr<Id> id;
    std::unique_ptr<Expr> expr;
    Set(std::unique_ptr<Id> _id, std::unique_ptr<Expr> _expr);
};