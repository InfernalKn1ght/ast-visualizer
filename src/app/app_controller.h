#pragma once

#include <QObject>

#include "app_view.h"
#include "ast_model.h"
#include "ast_model_creator.h"

/**
 * @brief The AppController class acts as the mediator between the View (AppView)
 * and the Model (ASTModel), handling user input and data flow.
 *
 * It manages the application's core logic, file operations, and the synchronization
 * between the source code input and the abstract syntax tree (AST) visualization.
 */
class AppController : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructs the application controller.
     *
     * Initializes the controller, links it to the View and Model components,
     * and processes command line arguments for initial file configuration.
     *
     * @param argc Number of command line arguments.
     * @param argv Array of command line argument strings.
     * @param view Pointer to the application's view component (GUI).
     * @param model Pointer to the application's AST data model.
     */
    AppController(int argc, char *argv[], AppView *view, ASTModel *model);

    /**
     * @brief Initializes the controller and starts the application logic.
     *
     * This typically includes configuring the initial file, performing the
     * first parsing operation, and displaying the initial AST model.
     */
    void init();

public slots:
    /**
     * @brief Handles requests indicating the source code text content has changed.
     *
     * This slot is usually connected to the view's text editor and triggers
     * a delayed or immediate AST update.
     */
    void handle_text_content_changed();

    /**
     * @brief Handles the request to save the current text editor content to file.
     *
     * After saving, this typically triggers an AST model update.
     */
    void handle_save_requested();

    /**
     * @brief Handles the request to load content from the configured file into
     * the text editor.
     */
    void handle_load_requested();

private:
    std::string file_name_;  ///< Path to the currently managed source file.

    AppView *view_;  ///< Pointer to the associated View component.
    ASTModel *model_;  ///< Pointer to the associated Model component.
    std::unique_ptr<AstModelCreator> creator_;  ///< Utility for creating the Qt visualization model from the AST.

    /**
     * @brief Configures the input file based on command line arguments.
     * @param argc Number of command line arguments.
     * @param argv Array of command line argument strings.
     * @return The name of the configured input file.
     */
    std::string configure_input_file(int argc, char *argv[]);

    /**
     * @brief Reads program arguments to find the input file name.
     * @param argc Number of command line arguments.
     * @param argv Array of command line argument strings.
     * @return The file name provided as argument, or an empty string.
     */
    std::string read_program_args(int argc, char *argv[]);

    /**
     * @brief Creates a default input file with basic content if it doesn't exist.
     * @param file_name The name of the default file to create.
     */
    void create_default_file(const std::string &file_name);

    /**
     * @brief Parses the source code, updates the AST model, and refreshes the view.
     *
     * This is the core synchronization method called after any relevant change.
     */
    void parse_and_update_view();

    static const std::string DEFAULT_FILE_NAME;  ///< Default file name used when no argument is provided.
};