#include "mainwindow.h"
#include "gamewindow.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    
    GameWindow g;
    g.show();

    return a.exec();
}
