#ifndef POOL_H
#define POOL_H

#include <pball.h>
#include <gscene.h>

#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QTimeLine>
#include <QDebug>

class Pool: public QObject
{
    Q_OBJECT
public:
    Pool();
    QVector<PBall*> getBallsAr();
public slots:
    void start();
private:
    QTimer* m_timer;
    GScene* m_scene;
    QVector<PBall*> m_balls; //16 шаров
    QVector<QGraphicsEllipseItem*> m_holes; //6 лунок
    QVector<QPushButton*> m_buttons; //3 кнопки
    QVBoxLayout* m_VLayout;
    QHBoxLayout* m_HLayout;
    QGraphicsView* m_view;
    QWidget* m_widget;
};

#endif // POOL_H
