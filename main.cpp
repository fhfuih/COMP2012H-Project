#include "mainwindow.h"
#include "OrbGameWindow.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(nullptr));
    QApplication a(argc, argv);

#ifdef RUN_MAINWINDOW
   MainWindow m;
    m.show();
#endif

#ifdef RUN_ORB_GAME_WINDOW
    OrbGameWindow g;
    g.show();
#endif

    return a.exec();
}
