#include "pool.h"
#include <QDebug>

Pool::Pool()
{
    m_widget = new QWidget(nullptr);
    m_widget->resize(600,600);
    m_widget->setWindowTitle("Бильярд");

    m_view = new QGraphicsView(m_widget);
    m_view->resize(400,530);

    qreal tHeight = m_view->height();
    qreal tWidth = m_view->width();

    QRectF sceneRectangle = QRectF(QPointF(0,0), QSizeF(tWidth,tHeight));
    m_scene = new GScene(sceneRectangle);
    m_view->setScene(m_scene);
    m_scene->balls = &m_balls;
    m_scene->setBackgroundBrush(Qt::darkGreen);

    m_VLayout = new QVBoxLayout;
    m_HLayout = new QHBoxLayout;

    m_HLayout->addWidget(m_view);
    m_HLayout->addLayout(m_VLayout);

    m_VLayout->addSpacing(20);
    m_VLayout->setContentsMargins(40,100,40,100);

    QString namesAr[3] = {"Начать", "Обновить стол", "Вернуть шар"};

    for(int i = 0; i < 3; i++)
    {
        m_buttons.insert(i, new QPushButton(namesAr[i]));
        m_VLayout->addWidget(m_buttons.at(i));
    }

    for(int i = 0; i < 15; i++)
    {
        m_balls.insert(i, new PBall(Qt::magenta, 0,0, QPoint(0,0)));
    }
    m_balls.insert(15, new PBall(Qt::white, 0,0, QPoint(0,0)));

    m_balls.at(0)->setPos(205,160);//
    m_balls.at(1)->setPos(190,145);
    m_balls.at(2)->setPos(220,145);//
    m_balls.at(3)->setPos(175,130);
    m_balls.at(4)->setPos(205,130);
    m_balls.at(5)->setPos(235,130);//
    m_balls.at(6)->setPos(160,115);
    m_balls.at(7)->setPos(190,115);
    m_balls.at(8)->setPos(220,115);
    m_balls.at(9)->setPos(250,115);//
    m_balls.at(10)->setPos(145,100);
    m_balls.at(11)->setPos(175,100);
    m_balls.at(12)->setPos(205,100);
    m_balls.at(13)->setPos(235,100);
    m_balls.at(14)->setPos(265,100);//

    m_balls.at(15)->setPos(205,450);

    for(int i = 0; i < 16; i++)
    {
        m_balls.at(i)->setRect(m_balls.at(i)->boundingRect());
    }

    m_holes.insert(0, new PBall(Qt::black, 0,0, QPoint(0,-10)));
    m_holes.insert(1, new PBall(Qt::black, 0,0, QPoint(0,120)));
    m_holes.insert(2, new PBall(Qt::black, 0,0, QPoint(0,275)));
    m_holes.insert(3, new PBall(Qt::black, 0,0, QPoint(200,-10)));
    m_holes.insert(4, new PBall(Qt::black, 0,0, QPoint(200,120)));
    m_holes.insert(5, new PBall(Qt::black, 0,0, QPoint(200,275)));

    m_widget->setLayout(m_HLayout);
    m_widget->show();

    m_timer = new QTimer;
    m_timer->setInterval(interval);

    connect(m_buttons.at(0), SIGNAL(clicked()), this, SLOT(start()));
    connect(m_buttons.at(2), SIGNAL(clicked()), m_scene, SLOT(resetBall()));
    connect(m_timer, SIGNAL(timeout()), m_scene, SLOT(advance()));

}

void Pool::start()
{
    for(int i = 0; i<16; i++)
    {
        m_scene->addItem(m_balls.at(i));
    }
    for(int i = 0; i < 6; i++)
    {
        m_scene->addItem(m_holes.at(i));
    }
    m_timer->start();
}

QVector<PBall*> Pool::getBallsAr()
{
    return m_balls;
}
