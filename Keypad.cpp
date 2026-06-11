#include "Keypad.hpp"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

Keypad::Keypad(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QGridLayout(this);

    layout->addWidget(new QPushButton("1"), 0, 0);
    layout->addWidget(new QPushButton("2"), 0, 1);
    layout->addWidget(new QPushButton("3"), 0, 2);
    layout->addWidget(new QPushButton("4"), 1, 0);
    layout->addWidget(new QPushButton("5"), 1, 1);
    layout->addWidget(new QPushButton("6"), 1, 2);
    layout->addWidget(new QPushButton("7"), 2, 0);
    layout->addWidget(new QPushButton("8"), 2, 1);
    layout->addWidget(new QPushButton("9"), 2, 2);
    layout->addWidget(new QPushButton("delete"), 3, 0);
    layout->addWidget(new QPushButton("0"), 3, 1);
    layout->addWidget(new QPushButton("enter"), 3, 2);
}
