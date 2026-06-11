#pragma once
#include <QMainWindow>
#include <QTimer>
#include "Keypad.hpp"
#include "displaypanel.hpp"

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
    DisplayPanel* dsp;
    QLabel* extraDisplay;
    Keypad* kyb;
};

