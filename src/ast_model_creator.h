#pragma once

#include <QStandardItemModel>

#include "parser.h"

/**
 * @brief Converts an AST into a Qt model for visualization.
 *
 * This class creates a QStandardItemModel that can be displayed as QTreeView.
 */
class AstModelCreator {
public:
    /**
     * @brief Creates and returns a Qt model representing the AST.
     * @return Pointer to a newly created QStandardItemModel containing the AST
     * structure.
     */
    QStandardItemModel *create_ast_model();

    /**
     * @brief Constructs an AstModelCreator and immediately parses the input
     * file.
     * @param file_name Path to the source file to be parsed.
     */
    AstModelCreator(const std::string &file_name);

    virtual ~AstModelCreator() = default;

private:
    std::unique_ptr<Node> ast_;  ///< Root node of the generated AST
    Parser parser_;              ///< Parser instance used to generate the AST
};