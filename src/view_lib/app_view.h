#pragma once

#include <QMainWindow>

#include "main_layout.h"

/**
 * @brief The AppView class represents the main application window and view component.
 *
 * This class serves as the top-level container for the user interface (UI) and
 * provides the external interface for the AppController to interact with the GUI,
 * abstracting the underlying MainLayout details.
 */
class AppView : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief Sets the initial content in the text editor field.
     * @param content The string content to be displayed initially.
     */
    void set_initial_content(const QString &content);

    /**
     * @brief Retrieves the current content from the text editor field.
     * @return The current source code content as a QString.
     */
    QString get_current_content() const;

    /**
     * @brief Updates the AST visualization component with a new data model.
     * @param model A pointer to the QAbstractItemModel representing the new AST structure.
     */
    void update_ast_visualization(QAbstractItemModel *model);

    /**
     * @brief Constructs the AppView window.
     * @param parent The parent widget (default is nullptr).
     */
    AppView(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal emitted when the text content in the editor changes.
     *
     * This connects the low-level UI event to the controller for model synchronization.
     */
    void text_content_changed();

    /**
     * @brief Signal emitted when the user requests a save operation.
     */
    void save_action_requested();

    /**
     * @brief Signal emitted when the user requests a load operation.
     */
    void load_action_requested();

private:
    MainLayout *main_layout_; ///< The central layout component handling the editor and visualization widgets.
};