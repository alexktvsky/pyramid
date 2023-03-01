#include <QApplication>

#include "main_window.h"


int main(int argc, char **argv) {

    QApplication app(argc, argv);

    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int screen_width = screenGeometry.width();
    int screen_height = screenGeometry.height();
    int width = 640;
    int height = 500;

    MainWindow mw;
    mw.setWindowTitle("Pyramid");
    mw.resize(width, height);
    mw.move((screen_width - width) / 2, (screen_height - height) / 2);
    mw.show();

    return app.exec();
}
