#include "Keypad.hpp"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "keyboard.h"
#include <cstdlib>

Keypad::Keypad(QWidget* parent)
    : QWidget(parent)
{
    auto* layout = new QGridLayout(this);
    auto makeButton = [&](const QString& text, int row, int col, char digit){
        auto* btn = new QPushButton(text, this);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        btn->setStyleSheet("QPushButton { padding: 20px 20px; }");
        layout->addWidget(btn, row, col);
        connect(btn, &QPushButton::clicked, this, [this, digit](){
            onButtonClicked(digit);
        });
    };
    makeButton("1", 0, 0, '1');
    makeButton("2", 0, 1, '2');
    makeButton("3", 0, 2, '3');
    makeButton("4", 1, 0, '4');
    makeButton("5", 1, 1, '5');
    makeButton("6", 1, 2, '6');
    makeButton("7", 2, 0, '7');
    makeButton("8", 2, 1, '8');
    makeButton("9", 2, 2, '9');
    makeButton("0", 3, 1, '0');

    auto* delBtn = new QPushButton("delete", this);
    delBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    delBtn->setStyleSheet("QPushButton { padding: 20px 20px; }");
    layout->addWidget(delBtn, 3, 0);
    connect(delBtn, &QPushButton::clicked, this, [this](){
        if (bufferIndex > 0) {
            bufferIndex--;
            keypadBuffer[bufferIndex] = ' ';
        };
    });
    
    auto* entBtn = new QPushButton("enter", this);
    entBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    entBtn->setStyleSheet("QPushButton { padding: 20px 20px; }");
    layout->addWidget(entBtn, 3, 2);
    connect(entBtn, &QPushButton::clicked, this, [this](){
        lastPressed = std::atoi(keypadBuffer);
    });

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 1);
    layout->setColumnMinimumWidth(0, 80);
    layout->setColumnMinimumWidth(1, 80);
    layout->setColumnMinimumWidth(2, 80);
    setLayout(layout);
}

void Keypad::onButtonClicked(char digit){
    if (bufferIndex < 4) {
        keypadBuffer[bufferIndex] = digit;
        bufferIndex++;
    }
}
