#pragma once
#include <QWidget>

class QLabel;

class DisplayPanel : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayPanel(QWidget* parent = nullptr);

    void updateDisplay();

private:
    QLabel* lcd;
};

