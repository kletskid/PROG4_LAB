#include "mainwindow.hpp"
extern "C" {
    #include "events.h"
    #include "fsm_functions/fsm.h"
}
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
   

   //setup ui
auto* central = new QWidget(this);
auto* layout = new QGridLayout(central);


//main display setup
this->dsp = new DisplayPanel(central);
layout->addWidget(this->dsp, 0, 0);

//keypad setup
this->kyb = new Keypad(central);
layout->addWidget(this->kyb, 1, 0);

//extra display setup

extraDisplay = new QLabel(central);
auto* extraContainer = new QWidget(central);
auto* extraLayout = new QVBoxLayout(extraContainer);

extraLayout->addWidget(extraDisplay);

extraDisplay->setText("Extra Display text here");
QFont font("Monospace");
font.setStyleHint(QFont::TypeWriter);
font.setPointSize(10);
extraDisplay->setFont(font);
extraDisplay->setAlignment(Qt::AlignLeft | Qt::AlignTop);
extraDisplay->setFrameStyle(QFrame::Panel | QFrame::Sunken);
extraDisplay->setStyleSheet(
    "QLabel {"
    "  background-color: #A8C686;"
    "  color: black;"
    "  border: 2px solid #4A5D23;"
    "}"
);
extraContainer->setVisible(false);
layout->addWidget(extraContainer, 0, 1, 3, 1);

setCentralWidget(central);

//extra display toggle button setup
auto* toggleContainer = new QWidget(central);
auto* toggleLayout = new QHBoxLayout(toggleContainer);
auto* toggleBtn = new QPushButton("Toggle Extra Display", central); // parent is central, not this
toggleLayout->addWidget(toggleBtn);
toggleBtn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
toggleBtn->setStyleSheet("QPushButton { padding: 20px 20px; }");
layout->addWidget(toggleContainer, 2, 0); // row 2, column 0 only
connect(toggleBtn, &QPushButton::clicked, this, [this, extraContainer](){
    extraContainer->setVisible(!extraContainer->isVisible());
    centralWidget()->adjustSize();
    adjustSize();
});

//adjust ui size
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
    this->dsp->updateDisplay();
    update();
}

