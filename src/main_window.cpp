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

    m_layer_combobox = new QComboBox(this);
    m_layer_combobox->setEnabled(false);
    connect(
        m_layer_combobox,
        qOverload<int>(&QComboBox::currentIndexChanged),
        this,
        &MainWindow::onActionselectLayer
    );
    statusBar()->addPermanentWidget(m_layer_combobox);
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

    QPixmap orig_pixmap(fname);
    m_label->setPixmap(orig_pixmap);
    m_label->resize(orig_pixmap.size());

    initializeImagePyramid(orig_pixmap);
    initializeComboBox();
}

void MainWindow::initializeImagePyramid(const QPixmap &pixmap)
{
    m_image_pyramid.clear();
    m_image_pyramid.push_back(pixmap);

    while (m_image_pyramid.back().width() > 1
        && m_image_pyramid.back().height() > 1)
    {
        QPixmap scaled_pixmap = m_image_pyramid.back().scaled(
            m_image_pyramid.back().width() / 2,
            m_image_pyramid.back().height() / 2
        );
        m_image_pyramid.push_back(scaled_pixmap);
    }
}

void MainWindow::initializeComboBox(void)
{
    m_layer_combobox->setEnabled(true);
    m_layer_combobox->clear();

    QString orig_image_name = tr("Original, Size: %1 x %2")
        .arg(m_image_pyramid.front().width())
        .arg(m_image_pyramid.front().height());

    m_layer_combobox->addItem(orig_image_name);

    for (size_t i = 1; i < m_image_pyramid.size(); ++i) {
        size_t width = m_image_pyramid[i].width();
        size_t height = m_image_pyramid[i].height();
        QString layer_name = tr("Layer: %1, Size: %2 x %3")
            .arg(i)
            .arg(width)
            .arg(height);
        m_layer_combobox->addItem(layer_name);
    }
}

void MainWindow::onActionselectLayer(int index)
{
    if (static_cast<size_t>(index) >= m_image_pyramid.size()) {
        return;
    }

    QPixmap layer = m_image_pyramid[index];

    if (index == 0) {
        m_label->setPixmap(layer);
    }
    else {

        int width = m_image_pyramid.front().width();
        int height = m_image_pyramid.front().height();

        QPixmap scaled_layer = layer.scaled(
            width,
            height,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );

        m_label->setPixmap(scaled_layer);
    }
}
