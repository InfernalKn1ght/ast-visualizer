#include "inter.h"

Node::Node(int _lexline) : lexline(_lexline) {}

Expr::Expr(std::unique_ptr<Token> _op) : op(std::move(_op)) {}

Expr::Expr(const Expr &expr) : op(expr.op->clone()) {}

Id::Id(const Id &id) {}