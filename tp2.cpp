#include <QPainter>
#include <QPainterPath>
#include "qevent.h"
#include "tp2.h"
#include "shape.h"
#include <iostream>

TP2::TP2()
{
    this->setMinimumSize(400, 300);
    this->lineColor = Qt::black;
    this->penStyle = Qt::SolidLine;
    this->penWidth = 1;
    image = QImage(800,800,QImage::Format_ARGB32);
}

void TP2::paintEvent(QPaintEvent* e){
    // standard behavior (draws the background)
/*
    QWidget::paintEvent(e);
    QPainter painter(this);
    painter.setPen(QPen(this->lineColor, this->penWidth, this->penStyle, Qt::RoundCap,Qt::RoundJoin));
    painter.drawPath(this->path);

*/QPainter painter(this);
    QRect dirtyRect = e->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void TP2::mousePressEvent(QMouseEvent* e){
    if (e->button() == Qt::LeftButton) {
        point = e->position().toPoint();
        this->path.moveTo(point);

     update();
    }
}

void TP2::mouseMoveEvent(QMouseEvent* e){
    //if (e->button() == Qt::LeftButton) {

    //update();

    //point = e->position().toPoint();
    this->path.lineTo(point);
    update();
    this->path.moveTo(point);
    //}
    if (this->activeShape == 0){drawLineTo(e->position().toPoint());}

}

void TP2::mouseReleaseEvent(QMouseEvent* e){
    if (this->activeShape == 1){
        drawRect(e->position().toPoint());
    } else if (this->activeShape == 2){
        drawEllipse(e->position().toPoint());
    }
}

void TP2::set_width(int width){
    this->penWidth = width;
    pen.setWidth(this->penWidth);
}

void TP2::set_color(QColor color){
    this->lineColor = color;
    pen.setBrush(this->lineColor);
}

void TP2::setLineStyle(int styleNumber){
    switch (styleNumber){
    case 0:
        this->penStyle = Qt::SolidLine;
        pen.setStyle(Qt::SolidLine);
        break;
    case 1:
        this->penStyle = Qt::DashLine;
        pen.setStyle(Qt::DashLine);
        break;
    case 2:
        this->penStyle = Qt::DotLine;
        pen.setStyle(Qt::DotLine);
        break;
    }
}

void TP2::setPenDefinitions(){
    pen.setStyle(this->penStyle);
    pen.setWidth(this->penWidth);
    pen.setBrush(this->lineColor);
}

void TP2::setActiveShape(int shapeNumber){
    this->activeShape = shapeNumber;
    std::cout << this->activeShape << std::endl;
}

void TP2::drawLineTo(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(this->lineColor, this->penWidth, this->penStyle, Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(point, endPoint);
    shape line(point.x(), point.y(), endPoint.x(), endPoint.y());
    shapes.push_back(line);
    //painter.drawPath(this->path);
    update();
    point = endPoint;
}

void TP2::drawRect(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(this->lineColor, this->penWidth, this->penStyle, Qt::RoundCap,Qt::RoundJoin));
    QRectF rect(point, endPoint);
    shape rectangle(point.x(), point.y(), endPoint.x(), endPoint.y());
    shapes.push_back(rectangle);
    painter.drawRect(rect);
    update();
    point = endPoint;
}

void TP2::drawEllipse(const QPoint &endPoint){
    QPainter painter(&image);
    painter.setPen(QPen(this->lineColor, this->penWidth, this->penStyle, Qt::RoundCap,Qt::RoundJoin));
    QRectF rect(point, endPoint);
    shape ellipse(point.x(), point.y(), endPoint.x(), endPoint.y());
    shapes.push_back(ellipse);
    painter.drawEllipse(rect);
    update();
    point = endPoint;
}

int TP2::get_width(){
    return this->penWidth;
}

