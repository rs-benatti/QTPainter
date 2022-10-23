#include <QPainter>
#include "tp2.h"

TP2::TP2()
{
    this->setMinimumSize(400, 300);
}

void TP2::paintEvent(QPaintEvent* e){
    // standard behavior (draws the background)
    QWidget::paintEvent(e);
     // creates a painter for this widget
    QPainter painter(this); // don't use new!
    painter.drawLine(50, 10, 100, 20);

}
