#include "displaypanel.hpp"
#include <QLabel>
#include <QFont>

DisplayPanel::DisplayPanel(QWidget* parent)
    : QWidget(parent)
{
    lcd = new QLabel(this);

    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);
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

    lcd->setFixedSize(width, height); 

    lcd->setText(
        "ABCDEFGHIJKLMNOPQRST\n"
        "ABCDEFGHIJKLMNOPQRST\n"
        "ABCDEFGHIJKLMNOPQRST\n"
        "ABCDEFGHIJKLMNOPQRST"
    );
}

