#ifndef TP2_H
#define TP2_H

#include <QWidget>


class TP2: public QWidget
{
    Q_OBJECT
public:
    TP2();

protected:
    virtual void paintEvent(QPaintEvent*);
};

#endif // TP2_H
