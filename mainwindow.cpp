#include "mainwindow.hpp"
extern "C" {
    #include "events.h"
    #include "fsm_functions/fsm.h"
    #include "coin_value.h"
}
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <QLabel>

int coin_value = -1; // Initialize coin_value to 0
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

extraDisplay->setText(R"(list of possible inputs:

product selection:
0: select cola classic 125c
1: select cola zero 160c
2: select diet coke 200c

maintenance mode:
6767: enter maintenance mode

money inserted while no product is selected will be returned immediately
)");
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
layout->addWidget(extraContainer, 0, 1, 4, 1);

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
auto* moneyContainer = new QWidget(central);
auto* moneyLayout = new QGridLayout(moneyContainer);
auto* coin20 = new QPushButton("Insert 20c", central);
auto* coin50 = new QPushButton("Insert 50c", central);
coin20->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
coin50->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
coin20->setStyleSheet("QPushButton { padding: 20px 20px; }");
coin50->setStyleSheet("QPushButton { padding: 20px 20px; }");
moneyLayout->addWidget(coin20, 0, 0);
moneyLayout->addWidget(coin50, 0, 1);
layout->addWidget(moneyContainer, 3, 0); // row 3, column 0 only
connect(coin20, &QPushButton::clicked, this, [this](){
    if (currentState == S_WAIT_FOR_MONEY) {
        coin_value = 20;
    }
    else {
        coin_value = -1; // Invalid state for inserting coins
    }
});
connect(coin50, &QPushButton::clicked, this, [this](){
    if (currentState == S_WAIT_FOR_MONEY) {
        coin_value = 50;
    }
    else {
        coin_value = -1; // Invalid state for inserting coins
    }
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

