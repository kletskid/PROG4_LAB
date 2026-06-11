#include "counterpanel.hpp"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

CounterPanel::CounterPanel(QWidget* parent)
    : QWidget(parent)
{
    label = new QLabel("Value: 0");
    incButton = new QPushButton("Increment");

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(incButton);

    connect(incButton, &QPushButton::clicked, this, [this]() {
        value++;
        label->setText(QString("Value: %1").arg(value));
    });
}
