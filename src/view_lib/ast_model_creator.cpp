#include "ast_model_creator.h"

#include <QStandardItem>

AstModelCreator::AstModelCreator(const Node *ast_root) : ast_root_(ast_root) {
    if (!ast_root_) {
        throw std::runtime_error("AstModelCreator received a null AST root.");
    }
}

QStandardItemModel *AstModelCreator::create_ast_model() {
    QStandardItemModel *model = new QStandardItemModel();

    convert_node(model->invisibleRootItem(), ast_root_);

    return model;
}

QStandardItem *AstModelCreator::convert_node(QStandardItem *parent_item,
                                             const Node *ast_node) {
    if (!ast_node) {
        return nullptr;
    }

    QStandardItem *current_item = nullptr;
    if (auto node = dynamic_cast<const Const *>(ast_node)) {
        QString caption =
            QString("[Const expression] ") + node->op_->token_string().c_str();

        current_item = new QStandardItem(caption);

    } else if (auto node = dynamic_cast<const Id *>(ast_node)) {
        QString caption =
            QString("[Id expression] ") + node->op_->token_string().c_str();

        current_item = new QStandardItem(caption);

    } else if (auto node = dynamic_cast<const UnaryOp *>(ast_node)) {
        QString caption = QString("[Unary operation expression] ") +
                          node->op_->token_string().c_str();
        current_item = new QStandardItem(caption);

        convert_node(current_item, node->expr_.get());

    } else if (auto node = dynamic_cast<const BinaryOp *>(ast_node)) {
        QString caption = QString("[Binary operation expression] ") +
                          node->op_->token_string().c_str();
        current_item = new QStandardItem(caption);

        convert_node(current_item, node->left_expr_.get());
        convert_node(current_item, node->right_expr_.get());
    } else if (auto node = dynamic_cast<const Stmts *>(ast_node)) {
        if (node->stmt_) {
            convert_node(parent_item, node->stmt_.get());
        }
        if (node->next_stmt_) {
            convert_node(parent_item, node->next_stmt_.get());
        }
        return nullptr;
    }

    else if (dynamic_cast<const Break *>(ast_node)) {
        current_item = new QStandardItem("[Statement] break");

    } else if (auto node = dynamic_cast<const Set *>(ast_node)) {
        current_item = new QStandardItem("[Assignment] =");

        convert_node(current_item, node->id_.get());
        convert_node(current_item, node->expr_.get());

    } else if (auto node = dynamic_cast<const If *>(ast_node)) {
        current_item = new QStandardItem("[Statement] if");

        convert_node(current_item, node->expr_.get());
        convert_node(current_item, node->stmt_.get());

    } else if (auto node = dynamic_cast<const IfElse *>(ast_node)) {
        current_item = new QStandardItem("[Statement] if else");

        convert_node(current_item, node->expr_.get());
        convert_node(current_item, node->stmt_.get());
        convert_node(current_item, node->else_stmt_.get());

    } else if (auto node = dynamic_cast<const While *>(ast_node)) {
        current_item = new QStandardItem("[Statement] while");

        convert_node(current_item, node->expr_.get());
        convert_node(current_item, node->stmt_.get());

    } else if (auto node = dynamic_cast<const Do *>(ast_node)) {
        current_item = new QStandardItem("[Statement] do while");

        convert_node(current_item, node->expr_.get());
        convert_node(current_item, node->stmt_.get());
    }

    if (current_item) {
        parent_item->appendRow(current_item);
    }

    return current_item;
}