#include "app_window.h"

const char *const WINDOW_TITLE = "Ast Visualizer";

AppWindow::AppWindow(const std::string &file_name)
    : creator_(std::make_unique<AstModelCreator>(file_name)) {
    setWindowTitle(WINDOW_TITLE);

    QWidget *central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    main_layout_ = new MainLayout(central_widget);
    main_layout_->set_ast_model(creator_->create_ast_model());

    central_widget->setLayout(main_layout_);

    connect(main_layout_, &MainLayout::request_model_update, this,
            &AppWindow::handle_model_update);
}

void AppWindow::handle_model_update() {
    if (main_layout_) {
        creator_.reset();
        creator_ = std::make_unique<AstModelCreator>("input.c");
        main_layout_->update_ast_model(creator_->create_ast_model());
    }
}