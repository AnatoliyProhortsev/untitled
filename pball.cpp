#include "pball.h"

PBall::PBall(QColor color, qreal speedX,qreal speedY, QPoint coord):
    QGraphicsEllipseItem(), m_coord(coord), m_speedX(speedX),
    m_speedY(speedY), m_color(color)
{
    this->setPos(coord);
    this->setRect(boundingRect());
}

QRectF PBall::boundingRect() const
{
    return QRectF(QPointF(m_coord.x()-ballR, m_coord.y()-ballR), QPointF(m_coord.x()+ballR, m_coord.y()+ballR));
}

QPolygonF PBall::BallPolygon() const
{
    qreal step = 360./100, curAngle = 0;
    QPolygonF polygon;

    for(int count = 0; count<100; count++)
    {
        qreal angleRad = curAngle*M_PI/180;
        polygon<<QPointF(this->x() + ballR*cos(angleRad), this->y() + ballR*sin(angleRad));
        curAngle+=step;
    }
    return polygon;
}

void PBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(m_color);
    painter->drawEllipse(m_coord, ballR, ballR);
}

void PBall::changeSpeed(qreal newSpeedX, qreal newSpeedY)
{
    m_speedX = newSpeedX;
    m_speedY = newSpeedY;
}
