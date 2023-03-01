#include "main_window.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QPixmap pixmap(500, 500);
    pixmap.fill(Qt::white);

    QLabel *label = new QLabel(this);
    label->setPixmap(pixmap);
    label->setAlignment(Qt::AlignCenter);
    setCentralWidget(label);
}
