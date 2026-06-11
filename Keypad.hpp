#pragma once
#include <QWidget>

class QLabel;
class QPushButton;

class Keypad : public QWidget
{
    Q_OBJECT
public:
    explicit Keypad(QWidget* parent = nullptr);

private slots:
    void onButtonClicked(char digit);

private:
    int bufferIndex= 0;
    QLabel* label;
    char keypadBuffer[4];
};

