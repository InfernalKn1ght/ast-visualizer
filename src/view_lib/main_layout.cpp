#include "main_layout.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

MainLayout::MainLayout(QWidget *parent, const std::string &file_name)
    : QHBoxLayout(parent) {
    setup_ui();
}

void MainLayout::setup_ui() {
    ast_view_ = new QTreeView();
    ast_view_->setHeaderHidden(true);
    addWidget(ast_view_);

    text_field_ = new QTextEdit();
    addWidget(text_field_);

    QVBoxLayout *button_layout = new QVBoxLayout();

    QPushButton *save_button = new QPushButton("Save");
    QPushButton *load_button = new QPushButton("Load");

    button_layout->addWidget(save_button);
    button_layout->addWidget(load_button);
    button_layout->addStretch();

    addLayout(button_layout);

    connect(save_button, &QPushButton::clicked, this,
            &MainLayout::save_requested);
    connect(load_button, &QPushButton::clicked, this,
            &MainLayout::load_requested);
    connect(text_field_, &QTextEdit::textChanged, this,
            &MainLayout::request_ast_update);
}

QString MainLayout::get_text_content() const {
    return text_field_->toPlainText();
}

void MainLayout::set_text_content(const QString &content) {
    text_field_->setPlainText(content);
}

void MainLayout::set_ast_model(QAbstractItemModel *model) {
    ast_view_->setModel(model);
}

void MainLayout::update_ast_model(QAbstractItemModel *model) {
    QAbstractItemModel *old_ast_model = ast_view_->model();
    if (old_ast_model) {
        old_ast_model->deleteLater();
    }

    set_ast_model(model);
}