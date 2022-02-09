#include "mainwindow.h"

#include "pball.h"
#include "pool.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pool mainPool;
    return a.exec();
}
