#include "ast_model.h"

#include <sstream>

#include "parser.h"

ASTModel::ASTModel() {}

Node* ASTModel::build_ast(const std::string& source_code) {
    const std::string TEMP_FILE_NAME = ".temp_ast_source.c";
    write_source_code(TEMP_FILE_NAME, source_code);

    Parser parser(TEMP_FILE_NAME);

    try {
        ast_root_ = std::move(parser.program());
        return ast_root_.get();
    } catch (const std::exception& e) {
        throw std::runtime_error("Parsing failed: " + std::string(e.what()));
    }
}

std::string ASTModel::read_source_code(const std::string& file_path) const {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        throw std::runtime_error("ASTModel: Cannot open file for reading: " +
                                 file_path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

void ASTModel::write_source_code(const std::string& file_path,
                                 const std::string& content) {
    std::ofstream file(file_path);

    if (!file.is_open()) {
        throw std::runtime_error("ASTModel: Cannot open file for writing: " +
                                 file_path);
    }

    file << content;

    if (file.fail()) {
        throw std::runtime_error("ASTModel: Error writing content to file: " +
                                 file_path);
    }
}