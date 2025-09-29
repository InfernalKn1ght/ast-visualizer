#pragma once

#include <QMainWindow>

#include "main_layout.h"

class AppView : public QMainWindow {
    Q_OBJECT
public:
    void set_initial_content(const QString &content);

    QString get_current_content() const;

    void update_ast_visualization(QAbstractItemModel *model);

    AppView(QWidget *parent = nullptr);

signals:
    void text_content_changed();
    void save_action_requested();
    void load_action_requested();

private:
    MainLayout *main_layout_;
};