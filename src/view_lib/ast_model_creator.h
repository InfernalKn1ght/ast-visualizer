#pragma once

#include <QStandardItemModel>
#include "inter.h" 

/**
 * @brief Converts an AST into a Qt model for visualization.
 *
 * This class acts as the Adapter/Presenter, converting the clean AST 
 * structure (Model) into the QStandardItemModel format required by QTreeView (View).
 */
class AstModelCreator {
public:
    /**
     * @brief Constructs an AstModelCreator with a clean AST root.
     * * @param ast_root Pointer to the root node of the already parsed AST.
     * The pointer is assumed to be valid for the lifetime of this object,
     * and ownership remains with the caller (ASTModel).
     */
    AstModelCreator(const Node *ast_root);

    /**
     * @brief Creates and returns a Qt model representing the AST.
     * @return Pointer to a newly created QStandardItemModel containing the AST
     * structure. The ownership of the returned model is passed to the caller (Controller).
     */
    QStandardItemModel *create_ast_model();

    virtual ~AstModelCreator() = default;

private:
    const Node *ast_root_; 

    QStandardItem *convert_node(QStandardItem *parent_item, const Node *ast_node);
};