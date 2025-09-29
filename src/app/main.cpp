#include <QApplication>

#include "app_controller.h"
#include "app_view.h"
#include "ast_model.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ASTModel model;
    AppView view;
    AppController controller(argc, argv, &view, &model);

    controller.init();
    view.show();

    return a.exec();
}