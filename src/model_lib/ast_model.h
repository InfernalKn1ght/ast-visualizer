#pragma once

#include "inter.h"

class ASTModel {
public:
    Node* build_ast(const std::string& source_code);
    std::string read_source_code(const std::string& file_path) const;
    void write_source_code(const std::string& file_path,
                           const std::string& content);

    ASTModel();

    virtual ~ASTModel() = default;

private:
    std::unique_ptr<Node> ast_root_ = nullptr;
};