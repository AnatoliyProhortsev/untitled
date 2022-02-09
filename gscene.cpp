#include<gscene.h>

GScene::GScene(QRectF sceneRect):QGraphicsScene() {
    this->setSceneRect(sceneRect);

}

void GScene::advance()
{
    QPointF secondPos;
    for (int i = 0; i < balls->count() ;i++)
    {
       colliding(balls->at(i));
       secondPos = QPointF(balls->at(i)->x() + balls->at(i)->getSpeedX(), balls->at(i)->y() + balls->at(i)->getSpeedY());
       balls->at(i)->setPos(secondPos);
       if(abs(balls->at(i)->getSpeedX()) <= 0.1)balls->at(i)->changeSpeed(0, balls->at(i)->getSpeedY()); else balls->at(i)->changeSpeed(balls->at(i)->getSpeedX() *quoff, balls->at(i)->getSpeedY());
       if(abs(balls->at(i)->getSpeedY()) <= 0.1)balls->at(i)->changeSpeed(balls->at(i)->getSpeedX(), 0); else balls->at(i)->changeSpeed(balls->at(i)->getSpeedX(),balls->at(i)->getSpeedY() *quoff);
    }
 }

void GScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt = event->scenePos();
    if(ballClickMode)
    {
        balls->at(15)->changeSpeed((balls->at(15)->x() - pt.x())/2, (balls->at(15)->y() - pt.y())/2);
    }else
    {
        balls->at(15)->show();
        balls->at(15)->setPos(pt.x(), pt.y());
        balls->at(15)->changeSpeed(0, 0);
        ballClickMode = !ballClickMode;
    }
}

void GScene::hitHole(int index)
{
    balls->at(index)->hide();
    balls->at(index)->setPos(-20,-20);
    balls->at(index)->changeSpeed(0,0);
}

void GScene::colliding(PBall* ball)
{
    QPolygonF polygon = ball->BallPolygon();
    qreal b1y = ball->y();
    qreal b1x = ball->x();
    qreal v1x = ball->getSpeedX();
    qreal v1y = ball->getSpeedY();

    for(int i = 0; i<balls->count(); i++)
    {
        if(polygon != balls->at(i)->BallPolygon())
        {
            if(polygon.intersects(balls->at(i)->BallPolygon()))
            {
                qreal b2x = balls->at(i)->x();
                qreal b2y = balls->at(i)->y();
                qreal v2x = balls->at(i)->getSpeedX();
                qreal v2y = balls->at(i)->getSpeedY();
                qreal v1Ox = v1x - (mass*v1x+mass*v2x)/(2*mass);
                qreal v1Oy = v1y - (mass*v1y+mass*v2y)/(2*mass);
                qreal vx = (mass*v1x+mass*v2x)/(2*mass); qreal vy = (mass*v1y+mass*v2y)/(2*mass);
                qreal v2Ox = v2x-vx; qreal v2Oy = v2y-vy;

                qreal rv1 = v1Ox*(b1x-b2x)+v1Oy*(b1y-b2y); qreal rv2 = v2Ox*(b2x-b1x)+v2Oy*(b2y-b1y);

                ball->changeSpeed(v1x - rv1/2/ballR/ballR*(b1x-b2x), v1y- rv2/2/ballR/ballR*(b1y-b2y));
                balls->at(i)->changeSpeed(v2x-rv2/2/ballR/ballR*(b2x-b1x), v2y-rv2/2/ballR/ballR*(b2y-b1y));



                if(b1x > b2x)ball->setPos(b1x+10,b1y); else if(b1x < b2x) ball->setPos(b1x-10,b1y);
                if(b1y > b2y)ball->setPos(b1x, b1y+10); else if(b1y > b2y) ball->setPos(b1x, b1y-10);
            }
        }

    }

    if(b1x <= 5)
    {
        if((b1y > 235 && b1y < 255) || (b1y < 5 && b1y > -10) || (b1y < 545 && b1y > 540))hitHole(balls->indexOf(ball));
        else
        {
            ball->setPos(5, b1y);
            ball->changeSpeed(-v1x, v1y);
        }
    }else if(ball->x() >= 395)
    {
        if((b1y > 235 && b1y < 255) || (b1y < 5 && b1y > -10) || (b1y < 545 && b1y > 540))hitHole(balls->indexOf(ball));
        else
        {
            ball->setPos(395, b1y);
            ball->changeSpeed(-v1x, v1y);
        }
    }

    if(ball->y() <= -10)
    {
        if((b1x < 7) || (b1x > 393))hitHole(balls->indexOf(ball));
        else
        {
            ball->setPos(b1x, -10);
            ball->changeSpeed(v1x, -v1y);
        }
    }else if(b1y >= 545)
    {
        if((b1x < 7) || (b1x > 393))hitHole(balls->indexOf(ball));
        else
        {
            ball->setPos(b1x, 545);
            ball->changeSpeed(v1x, -v1y);
        }
    }
}

void GScene::resetBall()
{
    ballClickMode = false;
}
