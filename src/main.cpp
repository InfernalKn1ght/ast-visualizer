#include <QApplication>
#include "app_window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    AppWindow window(argc, argv);

    window.show();

    return a.exec();
}