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
   * @param argc Number of command line arguments.
   * @param argv Array of command line argument strings.
   */
  AppWindow(int argc, char *argv[]);

public slots:
  /**
   * @brief Handles requests to update the AST model.
   *
   * This slot is triggered when the source code is modified and the AST needs
   * rebuilding. It recreates the AST model and updates the visualization.
   */
  void handle_model_update();

private:
  std::string file_name_;  ///< Path to the source file

  std::unique_ptr<AstModelCreator> creator_;  ///< Manages AST model creation
  MainLayout *main_layout_;                    ///< The central layout containing all UI components

  /**
   * @brief Configures the input file based on command line arguments.
   * @param argc Number of command line arguments.
   * @param argv Array of command line argument strings.
   * @return The name of the configured input file.
   */
  std::string configure_input_file(int argc, char *argv[]);

  /**
   * @brief Reads the program arguments from the command line.
   * @param argc Number of command line arguments.
   * @param argv Array of command line argument strings.
   * @return The file name provided as a command line argument, or an empty
   * string if no file name is provided.
   */
  std::string read_program_args(int argc, char *argv[]);

  /**
   * @brief Creates a default input file if it doesn't already exist.
   * @param file_name The name of the default file to create.
   */
  void create_default_file(const std::string &file_name);
};