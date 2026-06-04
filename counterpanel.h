#pragma once
#include <QWidget>

class QLabel;
class QPushButton;

class CounterPanel : public QWidget
{
    Q_OBJECT
public:
    explicit CounterPanel(QWidget* parent = nullptr);

private:
    int value = 0;
    QLabel* label;
    QPushButton* incButton;
};

