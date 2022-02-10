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
       secondPos = QPointF(balls->at(i)->x() + balls->at(i)->getSpeedX(),
                           balls->at(i)->y() + balls->at(i)->getSpeedY());

       balls->at(i)->setPos(secondPos);

       if(abs(balls->at(i)->getSpeedX()) <= 0.1)
           balls->at(i)->setSpeedX(0);
       else
           balls->at(i)->setSpeedX(balls->at(i)->getSpeedX() *FRICTION_QUOFF);

       if(abs(balls->at(i)->getSpeedY()) <= 0.1)
           balls->at(i)->setSpeedY(0);
       else
           balls->at(i)->setSpeedY(balls->at(i)->getSpeedY() *FRICTION_QUOFF);
    }
 }

void GScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt = event->scenePos();
    if(ballClickMode)
    {
        balls->at(15)->setSpeedX((balls->at(15)->x() - pt.x())/2);
        balls->at(15)->setSpeedY((balls->at(15)->y() - pt.y())/2);
    }else
    {
        balls->at(15)->show();
        balls->at(15)->setPos(pt.x(), pt.y());
        balls->at(15)->setSpeedX(0);
        balls->at(15)->setSpeedY(0);
        ballClickMode = !ballClickMode;
    }
}

void GScene::hitHole(int index)
{
    balls->at(index)->hide();
    balls->at(index)->setPos(-20,-20);
    balls->at(index)->setSpeedX(0);
    balls->at(index)->setSpeedY(0);
}

void GScene::colliding(PBall* ball)
{
    QPolygonF polygon = ball->getBallPolygon();
    qreal b1y = ball->y();
    qreal b1x = ball->x();
    qreal v1x = ball->getSpeedX();
    qreal v1y = ball->getSpeedY();

    for(int i = 0; i<balls->count(); i++)
    {
        if(polygon != balls->at(i)->getBallPolygon())
        {
            if(polygon.intersects(balls->at(i)->getBallPolygon()))
            {
                qreal b2x = balls->at(i)->x();
                qreal b2y = balls->at(i)->y();
                qreal v2x = balls->at(i)->getSpeedX();
                qreal v2y = balls->at(i)->getSpeedY();
                qreal v1Ox = v1x - (BALL_MASS*v1x+BALL_MASS*v2x)/(2*BALL_MASS);
                qreal v1Oy = v1y - (BALL_MASS*v1y+BALL_MASS*v2y)/(2*BALL_MASS);
                qreal vx = (BALL_MASS*v1x+BALL_MASS*v2x)/(2*BALL_MASS);
                qreal vy = (BALL_MASS*v1y+BALL_MASS*v2y)/(2*BALL_MASS);
                qreal v2Ox = v2x-vx; qreal v2Oy = v2y-vy;

                qreal rv1 = v1Ox*(b1x-b2x)+v1Oy*(b1y-b2y);
                qreal rv2 = v2Ox*(b2x-b1x)+v2Oy*(b2y-b1y);

                ball->setSpeedX(v1x - rv1/2/BALL_RADIUS/BALL_RADIUS*(b1x-b2x));
                ball->setSpeedY(v1y- rv2/2/BALL_RADIUS/BALL_RADIUS*(b1y-b2y));

                balls->at(i)->setSpeedX(v2x-rv2/2/BALL_RADIUS/BALL_RADIUS*(b2x-b1x));
                balls->at(i)->setSpeedY(v2y-rv2/2/BALL_RADIUS/BALL_RADIUS*(b2y-b1y));

                if(b1x > b2x)
                    ball->setPos(b1x+6,b1y);
                else if(b1x < b2x)
                    ball->setPos(b1x-6,b1y);

                if(b1y > b2y)
                    ball->setPos(b1x, b1y+6);
                else if(b1y > b2y)
                    ball->setPos(b1x, b1y-6);
            }
        }

    }

    if(b1x <= 5)
    {
        if((b1y > 235 && b1y < 255)
                || (b1y < 5 && b1y > -10)
                || (b1y < 545 && b1y > 540))
            hitHole(balls->indexOf(ball));
        else
        {
            ball->setPos(5, b1y);
            ball->setSpeedX(-v1x);
            ball->setSpeedY(v1y);
        }
    }else if(ball->x() >= 395)
    {
        if((b1y > 235 && b1y < 255)
                || (b1y < 5 && b1y > -10)
                || (b1y < 545 && b1y > 540))
            hitHole(balls->indexOf(ball));
        else
        {
            ball->setPos(395, b1y);
            ball->setSpeedX(-v1x);
            ball->setSpeedY(v1y);
        }
    }

    if(ball->y() <= -10)
    {
        if((b1x < 7) || (b1x > 393))
            hitHole(balls->indexOf(ball));
        else
        {
            ball->setPos(b1x, -10);
            ball->setSpeedX(v1x);
            ball->setSpeedY(-v1y);
        }
    }else if(b1y >= 545)
    {
        if((b1x < 7) || (b1x > 393))
            hitHole(balls->indexOf(ball));
        else
        {
            ball->setPos(b1x, 545);
            ball->setSpeedX(v1x);
            ball->setSpeedY(-v1y);
        }
    }
}

void GScene::resetBall(){ballClickMode = false;}
