#include "mainwindow.h"
#include "counterpanel.h"
#include <QWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    auto* central = new QWidget(this);
    auto* layout = new QVBoxLayout(central);

    auto* counter = new CounterPanel(central);
    layout->addWidget(counter);

    setCentralWidget(central);
}

