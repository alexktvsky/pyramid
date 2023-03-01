#include "main_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_label = new QLabel(this);
    m_label->setAlignment(Qt::AlignCenter);

    m_scroll_area = new QScrollArea(this);
    m_scroll_area->setWidgetResizable(true);
    m_scroll_area->setWidget(m_label);
    setCentralWidget(m_scroll_area);

    QMenuBar *menu_bar = new QMenuBar(this);
    setMenuBar(menu_bar);
    QMenu *file_menu = menu_bar->addMenu(tr("&File"));
    QAction *open_action = new QAction(tr("&Open Image"), this);
    open_action->setShortcut(QKeySequence("CTRL+O"));
    file_menu->addAction(open_action);
    connect(
        open_action,
        &QAction::triggered,
        this,
        &MainWindow::onActionOpenImage
    );
}

void MainWindow::onActionOpenImage(void)
{
    QString fname = QFileDialog::getOpenFileName(
        this,
        tr("Open image..."),
        QDir::currentPath(),
        "*.png *.jpg"
    );

    if (fname.isEmpty()) {
        return;
    }

    QPixmap pixmap(fname);
    m_label->setPixmap(pixmap);
    m_label->resize(pixmap.size());
}
