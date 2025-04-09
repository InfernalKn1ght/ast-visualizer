#pragma once

#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeView>

/**
 * @brief The MainLayout class represents the main layout of the application.
 *
 * This layout contains a text editor, a tree view for AST visualization,
 * and buttons for file operations.
 */
class MainLayout : public QHBoxLayout {
    Q_OBJECT
public:
    /**
     * @brief Constructs a MainLayout with optional parent widget.
     * @param parent The parent widget (default is nullptr).
     */
    MainLayout(QWidget *parent = nullptr);

    /**
     * @brief Sets the AST model for the tree view.
     * @param model The item model representing the AST.
     */
    void set_ast_model(QAbstractItemModel *model);

    /**
     * @brief Loads initial content from "input.c" file into the text editor.
     */
    void load_initial_content();

    /**
     * @brief Updates the AST model, deleting the old model if it exists.
     * @param model The new AST item model.
     */
    void update_ast_model(QAbstractItemModel *model);

signals:
    /**
     * @brief Signal emitted when a model update is requested (after saving).
     */
    void request_model_update();

private slots:
    /**
     * @brief Saves the text editor content to file.
     */
    void save_to_file();

    /**
     * @brief Loads content from "input.c" file into the text editor.
     */
    void load_from_file();

private:
    QTextEdit *text_field_;  ///< Text editor widget for code input.
    QTreeView *ast_view_;    ///< Tree view widget for AST visualization.

    /**
     * @brief Sets up the user interface components.
     *
     * Initializes and arranges the text editor, AST view, and buttons.
     * Connects button signals to appropriate slots.
     */
    void setup_ui();
};