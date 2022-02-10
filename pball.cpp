#include "pball.h"

PBall::PBall(QColor color, qreal speedX,qreal speedY, QPoint coord):
    QGraphicsEllipseItem(), m_coord(coord), m_speedX(speedX),
    m_speedY(speedY), m_color(color)
{
    setPos(coord);
    setRect(getBallRect());
}

QRectF PBall::getBallRect()
{
    return QRectF(QPointF(m_coord.x()-BALL_RADIUS, m_coord.y()-BALL_RADIUS),
                  QPointF(m_coord.x()+BALL_RADIUS, m_coord.y()+BALL_RADIUS));
}

QPolygonF PBall::getBallPolygon()
{
    qreal step = 360./100, curAngle = 0;
    QPolygonF polygon;

    for(int count = 0; count<100; count++)
    {
        qreal angleRad = curAngle*M_PI/180;
        polygon<<QPointF(this->x() + BALL_RADIUS*cos(angleRad),
                         this->y() + BALL_RADIUS*sin(angleRad));
        curAngle+=step;
    }
    return polygon;
}

void PBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(m_color);
    painter->drawEllipse(m_coord, BALL_RADIUS, BALL_RADIUS);
}

qreal PBall::getSpeedX(){return m_speedX;}
qreal PBall::getSpeedY(){return m_speedY;}

void PBall::setSpeedX(qreal speed){m_speedX = speed;}
void PBall::setSpeedY(qreal speed){m_speedY = speed;}


