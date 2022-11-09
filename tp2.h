#ifndef TP2_H
#define TP2_H

#include <QWidget>
#include <QPainterPath>
#include <QPen>
#include "shape.h"


class TP2: public QWidget
{
    Q_OBJECT
public:
    TP2();
    QPainterPath path;
    QPoint point;
    QPoint secondPoint;
    QList<shape> shapes;
    void set_color(QColor color);
    void set_width(int width);
    int get_width();
    void setLineStyle(int styleNumber);
    int activeShape = 0; // 0 for line, 1 for rectangle and 2 for ellipse
    void setActiveShape(int shapeNumber);

private:
    QColor lineColor;
    QPen pen;  // creates a default pen
    int penWidth;
    void setPenDefinitions();
    void drawLineTo(const QPoint &endPoint);
    void drawRect(const QPoint &endPoint);
    void drawEllipse(const QPoint &endPoint);
    Qt::PenStyle penStyle;
    QImage image;


protected:
    virtual void paintEvent(QPaintEvent*);

    virtual void mousePressEvent(QMouseEvent*);

    virtual void mouseMoveEvent(QMouseEvent*);

    virtual void mouseReleaseEvent(QMouseEvent*);

};

#endif // TP2_H
