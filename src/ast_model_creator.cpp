#include "ast_model_creator.h"

AstModelCreator::AstModelCreator(const std::string &file_name)
    : parser_(file_name) {
    ast_ = parser_.program();
}

QStandardItemModel *AstModelCreator::create_ast_model() {
    QStandardItemModel *ast_model = new QStandardItemModel();
    QStandardItem *parent_item = ast_model->invisibleRootItem();
    ast_->append_ast_model_node(parent_item);
    return ast_model;
}