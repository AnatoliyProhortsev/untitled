#include<gscene.h>

GScene::GScene(QRectF sceneRect):QGraphicsScene() {
    this->setSceneRect(sceneRect);

}

void GScene::advance()
{
    QPointF secondPos;
    for (int i = 0; i < balls->count() ;i++)
    {
        PBall* ball = balls->at(i);
        for(int j = i+1; j<balls->count(); j++)
        {
            if(ball->getBallPolygon().intersects(balls->at(j)->getBallPolygon()))
                colliding(ball, balls->at(j));
        }

       secondPos = QPointF(ball->x() + ball->getSpeedX(),
                           ball->y() + ball->getSpeedY());

       ball->setPos(secondPos);

       if(abs(ball->getSpeedX()) <= 0.1)
           ball->setSpeedX(0);
       else
           ball->setSpeedX(ball->getSpeedX() *FRICTION_QUOFF);

       if(abs(ball->getSpeedY()) <= 0.1)
           ball->setSpeedY(0);
       else
           ball->setSpeedY(ball->getSpeedY() *FRICTION_QUOFF);

       qreal x = ball->x();
       qreal y = ball->y();
       qreal v1x = ball->getSpeedX();
       qreal v1y = ball->getSpeedY();
       if(x <= 5)
           {
               if((y > 235 && y < 255)
                       || (y < 5 && y > -10)
                       || (y < 545 && y > 540))
                   hitHole(i);
               else
               {
                   ball->setPos(5, y);
                   ball->setSpeedX(-v1x);
                   ball->setSpeedY(v1y);
               }
           }else if(ball->x() >= 395)
           {
               if((y > 235 && y < 255)
                       || (y < 5 && y > -10)
                       || (y < 545 && y > 540))
                   hitHole(i);
               else
               {
                   ball->setPos(395, y);
                   ball->setSpeedX(-v1x);
                   ball->setSpeedY(v1y);
               }
           }

           if(y <= -10)
           {
               if((x < 7) || (x > 393))
                   hitHole(i);
               else
               {
                   ball->setPos(x, -10);
                   ball->setSpeedX(v1x);
                   ball->setSpeedY(-v1y);
               }
           }else if(y >= 545)
           {
               if((x < 7) || (x > 393))
                   hitHole(i);
               else
               {
                   ball->setPos(x, 545);
                   ball->setSpeedX(v1x);
                   ball->setSpeedY(-v1y);
               }
           }
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

void GScene::colliding(PBall* ball1, PBall* ball2)
{
    QPolygonF polygon = ball1->getBallPolygon();
    qreal b1y = ball1->y();
    qreal b1x = ball1->x();
    qreal v1x = ball1->getSpeedX();
    qreal v1y = ball1->getSpeedY();

    qreal b2x = ball2->x();
    qreal b2y = ball2->y();
    qreal v2x = ball2->getSpeedX();
    qreal v2y = ball2->getSpeedY();
    qreal v1Ox = v1x - (BALL_MASS*v1x+BALL_MASS*v2x)/(2*BALL_MASS);
    qreal v1Oy = v1y - (BALL_MASS*v1y+BALL_MASS*v2y)/(2*BALL_MASS);
    qreal vx = (BALL_MASS*v1x+BALL_MASS*v2x)/(2*BALL_MASS);
    qreal vy = (BALL_MASS*v1y+BALL_MASS*v2y)/(2*BALL_MASS);
    qreal v2Ox = v2x-vx; qreal v2Oy = v2y-vy;

    qreal rv1 = v1Ox*(b1x-b2x)+v1Oy*(b1y-b2y);
    qreal rv2 = v2Ox*(b2x-b1x)+v2Oy*(b2y-b1y);

    ball1->setSpeedX(v1x - rv1/2/BALL_RADIUS/BALL_RADIUS*(b1x-b2x));
    ball1->setSpeedY(v1y- rv2/2/BALL_RADIUS/BALL_RADIUS*(b1y-b2y));

    ball2->setSpeedX(v2x-rv2/2/BALL_RADIUS/BALL_RADIUS*(b2x-b1x));
    ball2->setSpeedY(v2y-rv2/2/BALL_RADIUS/BALL_RADIUS*(b2y-b1y));

    qreal d; //На какое расстояние шары "зашли" в друг друга (делённое на два)
    if(b1x > b2x)
    {
        d = (2*BALL_RADIUS - b1x + b2x)/2;
        ball1->setPos(b1x + d, b1y);
        ball2->setPos(b2x - d, b2y);
    }
    else
    {
        d = (2*BALL_RADIUS - b2x + b1x)/2;
        ball1->setPos(b1x - d, b1y);
        ball2->setPos(b2x + d, b2y);
    }
    if(b1y > b2y)
    {
        d = (2*BALL_RADIUS - b1y + b2y)/2;
        ball1->setPos(b1x, b1y + d);
        ball2->setPos(b2x, b2y - d);
    }
    else
    {
        d = (2*BALL_RADIUS - b2y + b1y)/2;
        ball1->setPos(b1x, b1y - d);
        ball2->setPos(b2x, b2y + d);
    }
}

void GScene::resetBall(){ballClickMode = false;}
