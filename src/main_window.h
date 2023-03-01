#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>


class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onActionOpenImage(void);

private:
    QLabel *m_label;
    QScrollArea *m_scroll_area;

}; // MainWindow


#endif // MAINWINDOW_H
