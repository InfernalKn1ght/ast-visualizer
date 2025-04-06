#include "inter.h"
#include <iostream>

Node::Node(int _lexline) : lexline(_lexline) {}

Expr::Expr(std::unique_ptr<Token> _op) : op(std::move(_op)) {}

Expr::Expr(const Expr &expr) : op(expr.op->clone()) {}

Id::Id(const Id &id) : Expr(id) {}

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

void UnaryOp::print(const std::string &prefix, bool has_left) const {}

void IfElse::print(const std::string &prefix, bool has_left) const {}

void While::print(const std::string &prefix, bool has_left) const {}

void Do::print(const std::string &prefix, bool has_left) const {}

void Break::print(const std::string &prefix, bool has_left) const {}