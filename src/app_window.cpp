#include "app_window.h"

const char *const WINDOW_TITLE = "Ast Visualizer";

AppWindow::AppWindow(const std::string &file_name) : creator(file_name) {
    setWindowTitle(WINDOW_TITLE);
    
    QWidget *central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    QStackedLayout *layout = new QStackedLayout(central_widget);

    QTreeView *ast_view = new QTreeView(central_widget);
    ast_view->setHeaderHidden(true);
    ast_view->setModel(creator.create_ast_model());

    layout->addWidget(ast_view);
}