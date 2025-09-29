#pragma once

#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeView>
#include <QAbstractItemModel> 

/**
 * @brief The MainLayout class represents the main layout of the application.
 *
 * This class is the primary View component for holding the source code editor 
 * and the AST visualization tree. It provides clear getters/setters for content 
 * and emits signals for user actions (Save, Load).
 */
class MainLayout : public QHBoxLayout {
    Q_OBJECT
public:
    /**
     * @brief Constructs a MainLayout with optional parent widget.
     * @param parent The parent widget (default is nullptr).
     * @param file_name The name of the input file (default is empty string).
     */
    MainLayout(QWidget *parent = nullptr, const std::string &file_name = "");

    /**
     * @brief Sets the AST model for the tree view.
     * * The model is set directly, and ownership may remain with the caller 
     * or be passed to the QTreeView, depending on its setup.
     * @param model The item model (QAbstractItemModel or derived) representing the AST structure.
     */
    void set_ast_model(QAbstractItemModel *model);

    /**
     * @brief Replaces the existing AST model in the tree view with a new one.
     * * This method correctly handles the deletion of the old model before setting the new one.
     * @param model The new AST item model (ownership is typically passed to the QTreeView/Qt system).
     */
    void update_ast_model(QAbstractItemModel *model);

    /**
     * @brief Retrieves the current content of the source code text editor.
     * * This method acts as a public interface for the Controller to read the user's input.
     * @return The current content of the QTextEdit as a QString.
     */
    QString get_text_content() const;

    /**
     * @brief Sets the content of the source code text editor.
     * * This method is used by the Controller to load initial content or content from file.
     * @param content The new QString content to display in the text editor.
     */
    void set_text_content(const QString &content);

signals:
    /**
     * @brief Signal emitted when the AST visualization needs to be rebuilt.
     *
     * Typically emitted after the text content is changed or saved, 
     * to notify the Controller that the Model should be re-parsed.
     */
    void request_ast_update();

    /**
     * @brief Signal emitted when the user clicks the "Save" button.
     *
     * Notifies the Controller to handle the actual file saving logic.
     */
    void save_requested();

    /**
     * @brief Signal emitted when the user clicks the "Load" button.
     *
     * Notifies the Controller to handle the actual file loading logic.
     */
    void load_requested();

private:
    QTextEdit *text_field_;  ///< The widget used for source code input.
    QTreeView *ast_view_;    ///< The widget used for displaying the AST structure.

    /**
     * @brief Sets up the user interface components.
     *
     * Initializes and arranges the text editor, AST view, and buttons,
     * connecting UI signals to the MainLayout's public signals.
     */
    void setup_ui();
};