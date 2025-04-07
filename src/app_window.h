#pragma once

#include "ast_model_creator.h"
#include "main_layout.h"
#include <QMainWindow>

class AppWindow : public QMainWindow {
    Q_OBJECT
public:
    AppWindow(const std::string &file_name);

public slots:
    void handle_model_update();

private:
    std::unique_ptr<AstModelCreator> creator;
    MainLayout *main_layout;
};