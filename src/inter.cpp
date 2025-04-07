#include "inter.h"
#include <iostream>

Node::Node(int _lexline) : lexline(_lexline) {}

Expr::Expr(std::unique_ptr<Token> _op) : op(std::move(_op)) {}

Expr::Expr(const Expr &expr) : op(expr.op->clone()) {}

Const::Const(std::unique_ptr<Token> _const_token) : Expr(std::move(_const_token)) {}

Id::Id(std::unique_ptr<Token> lexeme) : Expr(std::move(lexeme)) {}

Id::Id(const Id &id) : Expr(id) {}

Op::Op(std::unique_ptr<Token> _op) : Expr(std::move(_op)) {}

BinaryOp::BinaryOp(std::unique_ptr<Token> _op, std::unique_ptr<Expr> _left_expr, std::unique_ptr<Expr> _right_expr) : Op(std::move(_op)), left_expr(std::move(_left_expr)), right_expr(std::move(_right_expr)) {}

UnaryOp::UnaryOp(std::unique_ptr<Token> _op, std::unique_ptr<Expr> _expr) : Op(std::move(_op)), expr(std::move(_expr)) {}

Stmts::Stmts(std::unique_ptr<Stmt> _stmt, std::unique_ptr<Stmt> _next_stmt) : stmt(std::move(_stmt)), next_stmt(std::move(_next_stmt)) {}

If::If(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt) : expr(std::move(_expr)), stmt(std::move(_stmt)) {}

IfElse::IfElse(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _if_stmt, std::unique_ptr<Stmt> _else_stmt) : If(std::move(_expr), std::move(_if_stmt)), else_stmt(std::move(_else_stmt)) {}

While::While(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt) : expr(std::move(_expr)), stmt(std::move(_stmt)) {}

Do::Do(std::unique_ptr<Expr> _expr, std::unique_ptr<Stmt> _stmt) : expr(std::move(_expr)), stmt(std::move(_stmt)) {}

Set::Set(std::unique_ptr<Id> _id, std::unique_ptr<Expr> _expr) : id(std::move(_id)), expr(std::move(_expr)) {}

void Const::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──");
    op->print();
    std::cout << std::endl;
}

void Id::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──");
    op->print();
    std::cout << std::endl;
}

void BinaryOp::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──");
    op->print();
    std::cout << std::endl;
    left_expr->print(prefix + (has_left ? "│   " : "    "), 1);
    right_expr->print(prefix + (has_left ? "│   " : "    "), 0);
}

void Stmts::print(const std::string &prefix, bool has_left) const {
    if (stmt)
        stmt->print(prefix, has_left);
    if (next_stmt)
        next_stmt->print(prefix, has_left);
}

void If::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──") << "if" << std::endl;
    expr->print(prefix + (has_left ? "│   " : "    "), 1);
    stmt->print(prefix + (has_left ? "│   " : "    "), 1);
}

void Set::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──") << " = " << std::endl;
    id->print(prefix + (has_left ? "│   " : "    "), 1);
    expr->print(prefix + (has_left ? "│   " : "    "), 0);
}

void UnaryOp::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──");
    op->print();
    std::cout << std::endl;
    expr->print(prefix + (has_left ? "│   " : "    "), 0);
}

void IfElse::print(const std::string &prefix, bool has_left) const {}

void While::print(const std::string &prefix, bool has_left) const {}

void Do::print(const std::string &prefix, bool has_left) const {}

void Break::print(const std::string &prefix, bool has_left) const {}

void Const::append_ast_model_node(QStandardItem *parent) const {
    QString caption = QString("[Const expression] ") + op->token_string().c_str();
    QStandardItem *next = new QStandardItem(caption);
    parent->appendRow(next);
}

void Id::append_ast_model_node(QStandardItem *parent) const {
    QString caption = QString("[Id expression] ") + op->token_string().c_str();
    QStandardItem *next = new QStandardItem(caption);
    parent->appendRow(next);
}

void BinaryOp::append_ast_model_node(QStandardItem *parent) const {
    QString caption = QString("[Binary operation expression] ") + op->token_string().c_str();
    QStandardItem *next = new QStandardItem(caption);
    left_expr->append_ast_model_node(next);
    right_expr->append_ast_model_node(next);
    parent->appendRow(next);
}

void Stmts::append_ast_model_node(QStandardItem *parent) const {
    if (stmt) {
        stmt->append_ast_model_node(parent);
    }
    if (next_stmt) {
        next_stmt->append_ast_model_node(parent);
    }
}

void If::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] if");
    expr->append_ast_model_node(next);
    stmt->append_ast_model_node(next);
    parent->appendRow(next);
}

void Set::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Assignment] =");
    id->append_ast_model_node(next);
    expr->append_ast_model_node(next);
    parent->appendRow(next);
}

void UnaryOp::append_ast_model_node(QStandardItem *parent) const {
    QString caption = QString("[Unary operation expression] ") + op->token_string().c_str();
    QStandardItem *next = new QStandardItem(caption);
    expr->append_ast_model_node(next);
    parent->appendRow(next);
}

void IfElse::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] if else");
    expr->append_ast_model_node(next);
    stmt->append_ast_model_node(next);
    else_stmt->append_ast_model_node(next);
    parent->appendRow(next);
}

void While::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] while");
    expr->append_ast_model_node(next);
    stmt->append_ast_model_node(next);
    parent->appendRow(next);
}

void Do::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] do while");
    expr->append_ast_model_node(next);
    stmt->append_ast_model_node(next);
    parent->appendRow(next);
}

void Break::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] break");
    parent->appendRow(next);
}
