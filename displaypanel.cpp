#include "displaypanel.hpp"
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>

extern "C" {
#include "display.h"
}

DisplayPanel::DisplayPanel(QWidget* parent)
    : QWidget(parent)
{
    auto* displayLayout = new QVBoxLayout(this);
    lcd = new QLabel(this);
    displayLayout->addWidget(lcd);

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

    QFontMetrics fm(font);
    int width  = fm.horizontalAdvance('M') * 20;
    int height = fm.height() * 4;

    lcd->setMinimumSize(width, height);
    lcd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

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

