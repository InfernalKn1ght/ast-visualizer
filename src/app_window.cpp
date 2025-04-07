#include "app_window.h"

const char *const WINDOW_TITLE = "Ast Visualizer";

AppWindow::AppWindow(const std::string &file_name) : creator(std::make_unique<AstModelCreator>(file_name)) {
    setWindowTitle(WINDOW_TITLE);

    QWidget *central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    main_layout = new MainLayout(central_widget);
    main_layout->set_ast_model(creator->create_ast_model());

    central_widget->setLayout(main_layout);

    connect(main_layout, &MainLayout::request_model_update, this, &AppWindow::handle_model_update);
}

void AppWindow::handle_model_update() {
    if (main_layout) {
        creator.reset();
        creator = std::make_unique<AstModelCreator>("input.c");
        main_layout->update_ast_model(creator->create_ast_model());
    }
}