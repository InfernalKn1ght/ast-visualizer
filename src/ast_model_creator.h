#pragma once

#include "parser.h"
#include <QStandardItemModel>

class AstModelCreator {
public:
    QStandardItemModel *create_ast_model();
    AstModelCreator(const std::string &file_name);
    virtual ~AstModelCreator() = default;

private:
    std::unique_ptr<Node> ast;
    Parser p;
};