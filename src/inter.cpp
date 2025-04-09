#include "inter.h"

#include <iostream>

Node::Node(int lexline) : lexline_(lexline) {}

Expr::Expr(std::unique_ptr<Token> op) : op_(std::move(op)) {}

Expr::Expr(const Expr &expr) : op_(expr.op_->clone()) {}

Const::Const(std::unique_ptr<Token> const_token)
    : Expr(std::move(const_token)) {}

Id::Id(std::unique_ptr<Token> lexeme) : Expr(std::move(lexeme)) {}

Id::Id(const Id &id) : Expr(id) {}

Op::Op(std::unique_ptr<Token> op) : Expr(std::move(op)) {}

BinaryOp::BinaryOp(std::unique_ptr<Token> op, std::unique_ptr<Expr> left_expr,
                   std::unique_ptr<Expr> right_expr)
    : Op(std::move(op)),
      left_expr_(std::move(left_expr)),
      right_expr_(std::move(right_expr)) {}

UnaryOp::UnaryOp(std::unique_ptr<Token> op, std::unique_ptr<Expr> expr)
    : Op(std::move(op)), expr_(std::move(expr)) {}

Stmts::Stmts(std::unique_ptr<Stmt> stmt, std::unique_ptr<Stmt> next_stmt)
    : stmt_(std::move(stmt)), next_stmt_(std::move(next_stmt)) {}

If::If(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt)
    : expr_(std::move(expr)), stmt_(std::move(stmt)) {}

IfElse::IfElse(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> if_stmt,
               std::unique_ptr<Stmt> else_stmt)
    : If(std::move(expr), std::move(if_stmt)),
      else_stmt_(std::move(else_stmt)) {}

While::While(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt)
    : expr_(std::move(expr)), stmt_(std::move(stmt)) {}

Do::Do(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt)
    : expr_(std::move(expr)), stmt_(std::move(stmt)) {}

Set::Set(std::unique_ptr<Id> id, std::unique_ptr<Expr> expr)
    : id_(std::move(id)), expr_(std::move(expr)) {}

void Const::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──");
    op_->print();
    std::cout << std::endl;
}

void Id::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──");
    op_->print();
    std::cout << std::endl;
}

void BinaryOp::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──");
    op_->print();
    std::cout << std::endl;
    left_expr_->print(prefix + (has_left ? "│   " : "    "), 1);
    right_expr_->print(prefix + (has_left ? "│   " : "    "), 0);
}

void Stmts::print(const std::string &prefix, bool has_left) const {
    if (stmt_) stmt_->print(prefix, has_left);
    if (next_stmt_) next_stmt_->print(prefix, has_left);
}

void If::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──") << "if" << std::endl;
    expr_->print(prefix + (has_left ? "│   " : "    "), 1);
    stmt_->print(prefix + (has_left ? "│   " : "    "), 1);
}

void Set::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──") << " = " << std::endl;
    id_->print(prefix + (has_left ? "│   " : "    "), 1);
    expr_->print(prefix + (has_left ? "│   " : "    "), 0);
}

void UnaryOp::print(const std::string &prefix, bool has_left) const {
    std::cout << prefix << (has_left ? "├──" : "└──");
    op_->print();
    std::cout << std::endl;
    expr_->print(prefix + (has_left ? "│   " : "    "), 0);
}

void IfElse::print(const std::string &prefix, bool has_left) const {}

void While::print(const std::string &prefix, bool has_left) const {}

void Do::print(const std::string &prefix, bool has_left) const {}

void Break::print(const std::string &prefix, bool has_left) const {}

void Const::append_ast_model_node(QStandardItem *parent) const {
    QString caption =
        QString("[Const expression] ") + op_->token_string().c_str();
    QStandardItem *next = new QStandardItem(caption);
    parent->appendRow(next);
}

void Id::append_ast_model_node(QStandardItem *parent) const {
    QString caption = QString("[Id expression] ") + op_->token_string().c_str();
    QStandardItem *next = new QStandardItem(caption);
    parent->appendRow(next);
}

void BinaryOp::append_ast_model_node(QStandardItem *parent) const {
    QString caption =
        QString("[Binary operation expression] ") + op_->token_string().c_str();
    QStandardItem *next = new QStandardItem(caption);
    left_expr_->append_ast_model_node(next);
    right_expr_->append_ast_model_node(next);
    parent->appendRow(next);
}

void Stmts::append_ast_model_node(QStandardItem *parent) const {
    if (stmt_) {
        stmt_->append_ast_model_node(parent);
    }
    if (next_stmt_) {
        next_stmt_->append_ast_model_node(parent);
    }
}

void If::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] if");
    expr_->append_ast_model_node(next);
    stmt_->append_ast_model_node(next);
    parent->appendRow(next);
}

void Set::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Assignment] =");
    id_->append_ast_model_node(next);
    expr_->append_ast_model_node(next);
    parent->appendRow(next);
}

void UnaryOp::append_ast_model_node(QStandardItem *parent) const {
    QString caption =
        QString("[Unary operation expression] ") + op_->token_string().c_str();
    QStandardItem *next = new QStandardItem(caption);
    expr_->append_ast_model_node(next);
    parent->appendRow(next);
}

void IfElse::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] if else");
    expr_->append_ast_model_node(next);
    stmt_->append_ast_model_node(next);
    else_stmt_->append_ast_model_node(next);
    parent->appendRow(next);
}

void While::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] while");
    expr_->append_ast_model_node(next);
    stmt_->append_ast_model_node(next);
    parent->appendRow(next);
}

void Do::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] do while");
    expr_->append_ast_model_node(next);
    stmt_->append_ast_model_node(next);
    parent->appendRow(next);
}

void Break::append_ast_model_node(QStandardItem *parent) const {
    QStandardItem *next = new QStandardItem("[Statement] break");
    parent->appendRow(next);
}
