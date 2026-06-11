#pragma once
#include <QWidget>

class QLabel;
class QPushButton;

class Keypad : public QWidget
{
    Q_OBJECT
public:
    explicit Keypad(QWidget* parent = nullptr);

private:
    int value = 0;
    QLabel* label;
    QPushButton* incButton;
};

