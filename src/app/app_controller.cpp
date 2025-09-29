#include "app_controller.h"

#include <QDebug>
#include <QMessageBox>
#include <stdexcept>

#include "app_view.h"
#include "ast_model.h"
#include "ast_model_creator.h"

const std::string AppController::DEFAULT_FILE_NAME = "input.c";

std::string AppController::read_program_args(int argc, char *argv[]) {
    if (argc > 1) {
        const std::string file_name = argv[1];
        return file_name;
    }
    return "";
}

void AppController::create_default_file(const std::string &file_name) {
    const std::string DEFAULT_CONTENT = "{\nint i;\ni = 100;\n}";

    try {
        model_->read_source_code(file_name);
    } catch (const std::runtime_error &e) {
        try {
            model_->write_source_code(file_name, DEFAULT_CONTENT);
            qDebug() << "Created default file:"
                     << QString::fromStdString(file_name);
        } catch (const std::runtime_error &write_err) {
            QMessageBox::critical(view_, "Error",
                                  "Could not create default file: " +
                                      QString::fromStdString(write_err.what()));
        }
    }
}

std::string AppController::configure_input_file(int argc, char *argv[]) {
    std::string file_name = read_program_args(argc, argv);

    if (file_name.empty()) {
        file_name = DEFAULT_FILE_NAME;
        create_default_file(file_name);
    }

    return file_name;
}

AppController::AppController(int argc, char *argv[], AppView *view,
                             ASTModel *model)
    : QObject(view), view_(view), model_(model) {
    file_name_ = configure_input_file(argc, argv);

    connect(view_, &AppView::text_content_changed, this,
            &AppController::handle_text_content_changed);
    connect(view_, &AppView::save_action_requested, this,
            &AppController::handle_save_requested);
    connect(view_, &AppView::load_action_requested, this,
            &AppController::handle_load_requested);
}

void AppController::init() {
    try {
        std::string initial_content = model_->read_source_code(file_name_);
        view_->set_initial_content(QString::fromStdString(initial_content));

        if (initial_content.empty()) {
            parse_and_update_view();
        }

    } catch (const std::runtime_error &e) {
        QMessageBox::critical(
            view_, "Initialization Error",
            "Failed to read initial file: " + QString::fromStdString(e.what()));
    }
}

void AppController::parse_and_update_view() {
    QString source_code_qstr = view_->get_current_content();
    std::string source_code = source_code_qstr.toStdString();

    try {
        Node *ast_root = model_->build_ast(source_code);

        creator_.reset();
        creator_ = std::make_unique<AstModelCreator>(ast_root);

        QAbstractItemModel *qt_model = creator_->create_ast_model();

        view_->update_ast_visualization(qt_model);

    } catch (const std::runtime_error &e) {
        QMessageBox::warning(
            view_, "Parsing Error",
            "Code could not be parsed: " + QString::fromStdString(e.what()));
    }
}

void AppController::handle_text_content_changed() { parse_and_update_view(); }

void AppController::handle_save_requested() {
    QString source_code_qstr = view_->get_current_content();
    std::string source_code = source_code_qstr.toStdString();

    try {
        model_->write_source_code(file_name_, source_code);
        QMessageBox::information(
            view_, "Success",
            "File saved successfully to " + QString::fromStdString(file_name_));

        parse_and_update_view();

    } catch (const std::runtime_error &e) {
        QMessageBox::critical(
            view_, "Save Error",
            "Could not save file: " + QString::fromStdString(e.what()));
    }
}

void AppController::handle_load_requested() {
    try {
        std::string content = model_->read_source_code(file_name_);
        view_->set_initial_content(QString::fromStdString(content));
        QMessageBox::information(view_, "Success",
                                 "File loaded successfully from " +
                                     QString::fromStdString(file_name_));

    } catch (const std::runtime_error &e) {
        QMessageBox::critical(
            view_, "Load Error",
            "Could not load file: " + QString::fromStdString(e.what()));
    }
}