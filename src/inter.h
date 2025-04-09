#pragma once

#include <QStandardItemModel>
#include <memory>

#include "token.h"

/**
 * @brief Base class for all AST nodes.
 *
 * Provides common functionality for all nodes in the AST,
 * including line number tracking and visualization methods.
 */
class Node {
public:
    int lexline_ = 0;  ///< Line number where the node appears in source code

    /**
     * @brief Prints the node and its children to stdout in tree format.
     * @param prefix String prefix for tree visualization
     * @param has_left Flag indicating left sibling in tree
     */
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const = 0;

    /**
     * @brief Adds the node and its children to a Qt model for visualization.
     * @param parent Parent item in the Qt model
     */
    virtual void append_ast_model_node(QStandardItem *parent) const = 0;

    /**
     * @brief Constructs a Node with optional line number.
     * @param lexline Source code line number (default 0)
     */
    Node(int lexline = 0);

    virtual ~Node() = default;
};

/**
 * @brief Base class for all expression nodes.
 *
 * Extends Node with operator token storage capability.
 */
class Expr : public Node {
public:
    std::unique_ptr<Token> op_;  ///< Operator token for the expression

    virtual void print(const std::string &prefix,
                       bool has_left) const override = 0;
    virtual void append_ast_model_node(
        QStandardItem *parent) const override = 0;

    /**
     * @brief Constructs an Expr with optional operator token.
     * @param op Operator token (default nullptr)
     */
    Expr(std::unique_ptr<Token> op = nullptr);

    /**
     * @brief Copy constructor for Expr.
     * @param expr Expression to copy
     */
    Expr(const Expr &expr);

    virtual ~Expr() = default;
};

/**
 * @brief Represents constant values in the AST.
 */
class Const : public Expr {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    /**
     * @brief Constructs a Const with optional token.
     * @param const_token Constant token (default nullptr)
     */
    Const(std::unique_ptr<Token> const_token = nullptr);

    virtual ~Const() = default;
};

/**
 * @brief Represents identifier references in the AST.
 */
class Id : public Expr {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    /**
     * @brief Constructs an Id with optional lexeme token.
     * @param lexeme Identifier token (default nullptr)
     */
    Id(std::unique_ptr<Token> lexeme = nullptr);

    virtual ~Id() = default;

    /**
     * @brief Copy constructor for Id.
     * @param id Identifier to copy
     */
    Id(const Id &id);
};

/**
 * @brief Base class for operator expressions.
 */
class Op : public Expr {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override = 0;
    virtual void append_ast_model_node(
        QStandardItem *parent) const override = 0;

    /**
     * @brief Constructs an Op with operator token.
     * @param op Operator token
     */
    Op(std::unique_ptr<Token> op);

    virtual ~Op() = default;
};

/**
 * @brief Represents binary operations in the AST.
 */
class BinaryOp : public Op {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    std::unique_ptr<Expr> left_expr_;   ///< Left operand expression
    std::unique_ptr<Expr> right_expr_;  ///< Right operand expression

    /**
     * @brief Constructs a BinaryOp with operator and operands.
     * @param op Operator token
     * @param left_expr Left operand
     * @param right_expr Right operand
     */
    BinaryOp(std::unique_ptr<Token> op, std::unique_ptr<Expr> left_expr,
             std::unique_ptr<Expr> right_expr);
};

/**
 * @brief Represents unary operations in the AST.
 */
class UnaryOp : public Op {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    std::unique_ptr<Expr> expr_;  ///< Operand expression

    /**
     * @brief Constructs a UnaryOp with operator and operand.
     * @param op Operator token
     * @param expr Operand expression
     */
    UnaryOp(std::unique_ptr<Token> op, std::unique_ptr<Expr> expr);

    virtual ~UnaryOp() = default;
};

/**
 * @brief Base class for all statement nodes.
 */
class Stmt : public Node {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override = 0;
    virtual void append_ast_model_node(
        QStandardItem *parent) const override = 0;

    Stmt() {}
    virtual ~Stmt() {}
};

/**
 * @brief Represents a sequence of statements in the AST.
 */
class Stmts : public Stmt {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    std::unique_ptr<Stmt> stmt_;       ///< First statement in sequence
    std::unique_ptr<Stmt> next_stmt_;  ///< Subsequent statements

    /**
     * @brief Constructs a Stmts with two statements.
     * @param stmt First statement
     * @param next_stmt Next statement
     */
    Stmts(std::unique_ptr<Stmt> stmt, std::unique_ptr<Stmt> next_stmt);

    virtual ~Stmts() = default;
};

/**
 * @brief Represents an if statement in the AST.
 */
class If : public Stmt {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    std::unique_ptr<Expr> expr_;  ///< Condition expression
    std::unique_ptr<Stmt> stmt_;  ///< Then branch statement

    /**
     * @brief Constructs an If with condition and branch.
     * @param expr Condition expression
     * @param stmt Then branch statement
     */
    If(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt);

    virtual ~If() = default;
};

/**
 * @brief Represents an if-else statement in the AST.
 */
class IfElse : public If {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    std::unique_ptr<Stmt> else_stmt_;  ///< Else branch statement

    /**
     * @brief Constructs an IfElse with condition and both branches.
     * @param expr Condition expression
     * @param if_stmt Then branch statement
     * @param else_stmt Else branch statement
     */
    IfElse(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> if_stmt,
           std::unique_ptr<Stmt> else_stmt);

    virtual ~IfElse() = default;
};

/**
 * @brief Represents a while loop in the AST.
 */
class While : public Stmt {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    std::unique_ptr<Expr> expr_;  ///< Loop condition expression
    std::unique_ptr<Stmt> stmt_;  ///< Loop body statement

    /**
     * @brief Constructs a While with condition and body.
     * @param expr Condition expression
     * @param stmt Loop body statement
     */
    While(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt);

    virtual ~While() = default;
};

/**
 * @brief Represents a do-while loop in the AST.
 */
class Do : public Stmt {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    std::unique_ptr<Expr> expr_;  ///< Loop condition expression
    std::unique_ptr<Stmt> stmt_;  ///< Loop body statement

    /**
     * @brief Constructs a Do with condition and body.
     * @param expr Condition expression
     * @param stmt Loop body statement
     */
    Do(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt);

    virtual ~Do() = default;
};

/**
 * @brief Represents a break statement in the AST.
 */
class Break : public Stmt {
public:
    virtual void append_ast_model_node(QStandardItem *parent) const override;
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;

    Break() {}  // TODO: add pointer to enclosing stmt
    virtual ~Break() = default;
};

/**
 * @brief Represents an assignment statement in the AST.
 */
class Set : public Stmt {
public:
    virtual void print(const std::string &prefix = "",
                       bool has_left = 0) const override;
    virtual void append_ast_model_node(QStandardItem *parent) const override;

    std::unique_ptr<Id> id_;      ///< Target identifier
    std::unique_ptr<Expr> expr_;  ///< Assigned expression

    /**
     * @brief Constructs a Set with target and value.
     * @param id Target identifier
     * @param expr Value expression
     */
    Set(std::unique_ptr<Id> id, std::unique_ptr<Expr> expr);
};