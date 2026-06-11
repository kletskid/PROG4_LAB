#pragma once
#include <QMainWindow>
#include <QTimer>
extern "C" {
#include "states.h"
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void MainWindowUpdate();

private:
    QTimer timer;
    state_t currentState;
};

