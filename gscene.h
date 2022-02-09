#ifndef GSCENE_H
#define GSCENE_H

#include <pball.h>
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QTimeLine>
#include <QDebug>

class GScene: public QGraphicsScene
{
    Q_OBJECT
public:
    GScene(QRectF sceneRect);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hitHole(int index);
    void colliding(PBall* ball);
    QVector<PBall*>* balls;
    bool ballClickMode = true;
public slots:
    void advance();
    void resetBall();
};
#endif // GSCENE_H
