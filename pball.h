#ifndef PBALL_H
#define PBALL_H

#include <QApplication>
#include <QObject>
#include <QGraphicsView>
#include <QCoreApplication>
#include <QLayout>
#include <QPushButton>
#include <QGraphicsItem>
#include <QtMath>
#include <vector>
#include <QPainter>
#include <QTimer>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <iterator>

const int ballR = 10;
const qreal quoff = 0.95;
const int mass = 10;
const int interval = 25;
const qreal impSpread = 5.0;

class PBall: public QGraphicsEllipseItem, public QObject
{
public:
    PBall(QColor color, qreal speedX,qreal speedY, QPoint coord);
    QRectF boundingRect() const;
    QPolygonF BallPolygon() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    qreal getSpeedX() {return m_speedX;}
    qreal getSpeedY() {return m_speedY;}
    void changeSpeed(qreal newSpeedX, qreal newSpeedY);
private:
    QPoint m_coord;
    qreal m_speedX, m_speedY;
    QColor m_color;
};
#endif // PBALL_H
