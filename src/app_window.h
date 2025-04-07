#pragma once

#include "ast_model_creator.h"
#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <QTreeView>

class AppWindow : public QMainWindow {
public:
    AppWindow(const std::string &file_name);
    // TODO: what about destructor
private:
    AstModelCreator creator;
};