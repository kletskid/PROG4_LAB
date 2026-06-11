#include "displaypanel.hpp"
#include <QLabel>
#include <QFont>

extern "C" {
#include "display.h"
}

DisplayPanel::DisplayPanel(QWidget* parent)
    : QWidget(parent)
{
    
    lcd = new QLabel(this);
    
    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    font.setPointSize(12);

    lcd->setFont(font);
    lcd->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    lcd->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    lcd->setStyleSheet(
        "QLabel {"
        "  background-color: #A8C686;"
        "  color: black;"
        "  border: 2px solid #4A5D23;"
        "}"
    );

    lcd->setText(
        "ABCDEFGHIJKLMNOPQRST\n"
        "ABCDEFGHIJKLMNOPQRST\n"
        "ABCDEFGHIJKLMNOPQRST\n"
        "ABCDEFGHIJKLMNOPQRST"
    );
}

void DisplayPanel::updateDisplay()
{
    char buffer[21*4];
    snprintf(buffer, 21*4, "%s\n%s\n%s\n%s", dsp_buffer[0], dsp_buffer[1], dsp_buffer[2], dsp_buffer[3]);
    lcd->setText(buffer);
}

