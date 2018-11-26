#include "mainwindow.h"
#include "OrbGameWindow.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    
    OrbGameWindow g;
    g.show();

    return a.exec();
}
