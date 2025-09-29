#pragma once

#include <QObject>

#include "app_view.h"
#include "ast_model.h"
#include "ast_model_creator.h"

class AppController : public QObject {
    Q_OBJECT
public:
    AppController(int argc, char *argv[], AppView *view, ASTModel *model);

    void init();

public slots:
    void handle_text_content_changed();

    void handle_save_requested();

    void handle_load_requested();

private:
    std::string file_name_;

    AppView *view_;
    ASTModel *model_;
    std::unique_ptr<AstModelCreator> creator_;

    std::string configure_input_file(int argc, char *argv[]);
    std::string read_program_args(int argc, char *argv[]);
    void create_default_file(const std::string &file_name);

    void parse_and_update_view();

    static const std::string DEFAULT_FILE_NAME;
};