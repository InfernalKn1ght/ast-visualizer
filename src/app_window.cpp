#include "app_window.h"

#include <memory>
#include <string>

#include "ast_model_creator.h"

const char *const WINDOW_TITLE = "Ast Visualizer";

const std::string DEFAULT_FILE_NAME = "input.c";

AppWindow::AppWindow(int argc, char *argv[])
    : file_name_(configure_input_file(argc, argv)),
      creator_(std::make_unique<AstModelCreator>(file_name_)) {
    setWindowTitle(WINDOW_TITLE);

    QWidget *central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    main_layout_ = new MainLayout(central_widget, file_name_);
    main_layout_->set_ast_model(creator_->create_ast_model());

    central_widget->setLayout(main_layout_);

    connect(main_layout_, &MainLayout::request_model_update, this,
            &AppWindow::handle_model_update);
}

void AppWindow::handle_model_update() {
    if (main_layout_) {
        creator_.reset();
        creator_ = std::make_unique<AstModelCreator>(file_name_);
        main_layout_->update_ast_model(creator_->create_ast_model());
    }
}

std::string AppWindow::configure_input_file(int argc, char *argv[]) {
    std::string file_name = read_program_args(argc, argv);

    if (file_name.empty()) {
        file_name = DEFAULT_FILE_NAME;
        create_default_file(file_name);
    }

    return file_name;
}

std::string AppWindow::read_program_args(int argc, char *argv[]) {
    if (argc > 1) {
        const std::string file_name = argv[1];
        return file_name;
    }
    return "";
}

void AppWindow::create_default_file(const std::string &file_name) {
    std::ifstream test_file(file_name);
    if (test_file.good()) {
        test_file.close();
        return;
    }

    std::ofstream file(file_name);
    if (file) {
        file.close();
    }
}