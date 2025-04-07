#pragma once

#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QTreeView>

class MainLayout : public QHBoxLayout {
    Q_OBJECT
public:
    MainLayout(QWidget *parent = nullptr);
    void set_ast_model(QAbstractItemModel *model);
    void load_initial_content();
    void update_ast_model(QAbstractItemModel *model);

signals:
    void request_model_update();

private slots:
    void save_to_file();
    void load_from_file();

private:
    QTextEdit *text_field;
    QTreeView *ast_view;
    void setup_ui();
};