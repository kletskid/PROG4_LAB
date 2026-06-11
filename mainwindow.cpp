#include "mainwindow.hpp"
#include "Keypad.hpp"
#include "displaypanel.hpp"

extern "C" {
    #include "events.h"
    #include "fsm_functions/fsm.h"
}
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
   

    //setup ui
    auto* central = new QWidget(this);
    auto* layout = new QGridLayout(central);

    auto* displaypanel = new DisplayPanel(central);
    layout->addWidget(Keypad);

    auto* keypad = new Keypad(central);
    layout->addWidget(keypad);

    setCentralWidget(central);
    this->adjustSize();
    
    //setup fsm
    this->currentState = S_IDLE;
    FSM_AddEvent(E_INITIALIZE);
    
    //setup update loop
    connect(&this->timer, &QTimer::timeout, this, &MainWindow::MainWindowUpdate);
    this->timer.start(16); //60 fps update loop
}

void MainWindow::MainWindowUpdate()
{
    currentState = FSM_UpdateStateMachine(this->currentState);
    update();
}

