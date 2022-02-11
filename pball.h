#ifndef PBALL_H
#define PBALL_H

#include <constants.h>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QtMath>
#include <QPainter>

class PBall: public QGraphicsEllipseItem, public QObject
{
public:
    PBall(QColor color, qreal speedX, qreal speedY, QPoint pos);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    qreal getSpeedX();
    qreal getSpeedY();
    void setSpeedX(qreal speed);
    void setSpeedY(qreal speed);
    QPolygonF getBallPolygon();
    QRectF getBallRect();
private:
    QRectF m_rect;
    QPolygonF m_polygon;
    QPoint m_coord;
    qreal m_speedX, m_speedY;
    QColor m_color;
};
#endif // PBALL_H
