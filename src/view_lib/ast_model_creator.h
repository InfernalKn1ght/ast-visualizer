#pragma once

#include <QStandardItemModel>
#include "inter.h" 

/**
 * @brief The AstModelCreator class acts as an Adapter/Presenter for AST visualization.
 *
 * This class is responsible for converting the language-agnostic Abstract Syntax 
 * Tree (AST) structure (the Model) into the QStandardItemModel format required 
 * by Qt's QTreeView (the View). It decouples the core logic from the Qt framework.
 */
class AstModelCreator {
public:
    /**
     * @brief Constructs an AstModelCreator, initializing it with the root of the AST.
     *
     * @param ast_root Pointer to the root node of the already parsed AST.
     * The pointer is assumed to be valid for the lifetime of this object,
     * and ownership remains with the caller (ASTModel).
     */
    AstModelCreator(const Node *ast_root);

    /**
     * @brief Creates and returns a Qt model representing the AST structure.
     * * This method traverses the AST and builds a QStandardItemModel suitable 
     * for display in a QTreeView.
     * * @return Pointer to a newly created QStandardItemModel. 
     * The ownership of the returned model is passed to the caller (Controller).
     */
    QStandardItemModel *create_ast_model();

    /**
     * @brief Default virtual destructor.
     */
    virtual ~AstModelCreator() = default;

private:
    const Node *ast_root_; ///< Raw pointer to the root of the AST (owned by ASTModel).

    /**
     * @brief Recursively converts an AST node and its children into QStandardItems.
     *
     * @param parent_item The QStandardItem under which the new node will be appended.
     * @param ast_node The current Node object from the AST to convert.
     * @return A pointer to the newly created QStandardItem corresponding to ast_node.
     */
    QStandardItem *convert_node(QStandardItem *parent_item, const Node *ast_node);
};