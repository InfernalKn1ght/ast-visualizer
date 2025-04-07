#include "main_layout.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


MainLayout::MainLayout(QWidget *parent) : QHBoxLayout(parent) {
    setup_ui();
    load_initial_content();
}

void MainLayout::setup_ui() {
    ast_view = new QTreeView();
    ast_view->setHeaderHidden(true);
    addWidget(ast_view);

    text_field = new QTextEdit();
    addWidget(text_field);

    QVBoxLayout *button_layout = new QVBoxLayout();
    
    QPushButton *save_button = new QPushButton("Save");
    QPushButton *load_button = new QPushButton("Load");
    
    button_layout->addWidget(save_button);
    button_layout->addWidget(load_button);
    button_layout->addStretch();
    
    addLayout(button_layout);

    connect(save_button, &QPushButton::clicked, this, &MainLayout::save_to_file);
    connect(load_button, &QPushButton::clicked, this, &MainLayout::load_from_file);
}

void MainLayout::set_ast_model(QAbstractItemModel *model) {
    ast_view->setModel(model);
}

void MainLayout::load_initial_content() {
    QFile file("input.c");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        text_field->setPlainText(in.readAll());
        file.close();
    }
}

void MainLayout::save_to_file() {
    QFile file("input.c");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << text_field->toPlainText();
        file.close();

        emit request_model_update();
    } else {
        QMessageBox::warning(nullptr, "Error", "Could not open file for writing");
    }
}

void MainLayout::load_from_file() {
    QFile file("input.c");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        text_field->setPlainText(in.readAll());
        file.close();
    } else {
        QMessageBox::warning(nullptr, "Error", "Could not open file for reading");
    }
}

void MainLayout::update_ast_model(QAbstractItemModel *model) {
    QAbstractItemModel *old_ast_model = ast_view->model();
    if (old_ast_model) {
        old_ast_model->deleteLater();
    }
    
    set_ast_model(model);
}