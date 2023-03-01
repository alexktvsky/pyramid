#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <QtWidgets>


class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onActionOpenImage(void);
    void onActionselectLayer(int index);

private:
    void initializeImagePyramid(const QPixmap &pixmap);
    void initializeComboBox(void);

private:
    QLabel *m_label;
    QScrollArea *m_scroll_area;
    std::vector<QPixmap> m_image_pyramid;
    QComboBox *m_layer_combobox;
}; // MainWindow


#endif // MAINWINDOW_H
