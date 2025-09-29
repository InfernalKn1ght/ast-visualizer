#pragma once

#include "inter.h"

/**
 * @brief The ASTModel class manages the Abstract Syntax Tree (AST) data structure.
 *
 * This class serves as the core data component, responsible for building the
 * AST from source code, and providing access to file I/O operations necessary
 * for interacting with the compiler's input.
 */
class ASTModel {
public:
    /**
     * @brief Parses the provided source code and builds the AST.
     *
     * The built AST is stored internally and its root is returned.
     * @param source_code The string containing the program source code.
     * @return A raw pointer to the root node of the internally managed AST.
     * The caller should NOT take ownership of this pointer.
     */
    Node* build_ast(const std::string& source_code);

    /**
     * @brief Reads the entire content of a specified file.
     * @param file_path The path to the file to be read.
     * @return A string containing the entire content of the file.
     */
    std::string read_source_code(const std::string& file_path) const;

    /**
     * @brief Writes the given content to a specified file.
     * @param file_path The path to the file to be written.
     * @param content The string content to write into the file.
     */
    void write_source_code(const std::string& file_path,
                           const std::string& content);

    /**
     * @brief Constructs an ASTModel instance.
     */
    ASTModel();

    /**
     * @brief Destructor for ASTModel.
     */
    virtual ~ASTModel() = default;

private:
    std::unique_ptr<Node> ast_root_ = nullptr; ///< The unique pointer holding the root of the AST.
};