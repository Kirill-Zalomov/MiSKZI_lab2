#include "controller.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    Controller mainWindow;
    mainWindow.show();
    return application.exec();
}
