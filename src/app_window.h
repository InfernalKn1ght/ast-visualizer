#pragma once

#include <QMainWindow>

#include "ast_model_creator.h"
#include "main_layout.h"

/**
 * @brief The main application window for AST visualization.
 */
class AppWindow : public QMainWindow {
    Q_OBJECT
public:
    /**
     * @brief Constructs the application window with initial file content.
     * @param file_name Path to the source file to visualize.
     */
    AppWindow(const std::string &file_name);

public slots:
    /**
     * @brief Handles requests to update the AST model.
     *
     * This slot is triggered when the source code is modified and the AST needs
     * rebuilding. It recreates the AST model and updates the visualization.
     */
    void handle_model_update();

private:
    std::unique_ptr<AstModelCreator> creator_;  ///< Manages AST model creation
    MainLayout
        *main_layout_;  ///< The central layout containing all UI components
};