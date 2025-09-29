#include "app_view.h"


const char *const WINDOW_TITLE = "Ast Visualizer";

AppView::AppView(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle(WINDOW_TITLE);

    QWidget *central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    main_layout_ = new MainLayout(central_widget);
    central_widget->setLayout(main_layout_);

    connect(main_layout_, &MainLayout::request_ast_update, this,
            &AppView::text_content_changed);
    connect(main_layout_, &MainLayout::save_requested, this,
            &AppView::save_action_requested);
    connect(main_layout_, &MainLayout::load_requested, this,
            &AppView::load_action_requested);
}

void AppView::set_initial_content(const QString &content) {
    main_layout_->set_text_content(content);
}

QString AppView::get_current_content() const {
    return main_layout_->get_text_content();
}

void AppView::update_ast_visualization(QAbstractItemModel *model) {
    main_layout_->update_ast_model(model);
}